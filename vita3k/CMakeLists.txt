set(VITA3K_ORG_NAME "Vita3K")
set(VITA3K_APP_NAME "Vita3K")
set(VITA3K_APP_ID "org.vita3k.vita3k")
set(VITA3K_APP_VER_HI 0)
set(VITA3K_APP_VER_MID 2)
set(VITA3K_APP_VER_LO 1)
set(VITA3K_APP_VERSION "v${VITA3K_APP_VER_HI}.${VITA3K_APP_VER_MID}.${VITA3K_APP_VER_LO}")

execute_process(
	COMMAND git rev-list HEAD --count
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_COUNT
	OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
	COMMAND git rev-parse --short HEAD
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_HASH
	OUTPUT_STRIP_TRAILING_WHITESPACE)

# Value is different when is PR
if("$ENV{GITHUB_EVENT_NAME}" STREQUAL "pull_request")
	set(GIT_BRANCH "$ENV{GITHUB_HEAD_REF}")
	if(WIN32)
		set(CMD powershell "(Get-Content $ENV{GITHUB_EVENT_PATH} | ConvertFrom-Json).pull_request.head.repo.html_url")
	else()
		set(CMD bash -c "jq .pull_request.head.repo.html_url $ENV{GITHUB_EVENT_PATH} | tr -d \\\" ")
	endif()
else()
	execute_process(
		COMMAND git rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	set(CMD git config --get remote.origin.url)
endif()

execute_process(COMMAND ${CMD}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_REPO
	OUTPUT_STRIP_TRAILING_WHITESPACE)

set(VITA3K_OFFICIAL_UPDATE_BUILD 0)

if (NOT GIT_REPO STREQUAL "")
	string(FIND ${GIT_REPO} "git@github.com:" IS_GIT_SSH)
	if (IS_GIT_SSH EQUAL 0)
		string(REPLACE "git@github.com:" "" GIT_REPO ${GIT_REPO})
	else()
		string(REPLACE "https://github.com/" "" GIT_REPO ${GIT_REPO})
	endif()
	string(REPLACE "/" ";" GIT_REPO ${GIT_REPO})
	list(POP_BACK GIT_REPO)
endif()

# The core's version is upstream Vita3K's, the build number and commit of the
# upstream it is built on (upstream.version, replaced with each merge of it),
# not counted from this repository's own commits
if(EXISTS "${CMAKE_SOURCE_DIR}/upstream.version")
	file(STRINGS "${CMAKE_SOURCE_DIR}/upstream.version" UPSTREAM_VERSION LIMIT_COUNT 1)
	string(REPLACE " " ";" UPSTREAM_VERSION "${UPSTREAM_VERSION}")
	list(GET UPSTREAM_VERSION 0 GIT_COUNT)
	list(GET UPSTREAM_VERSION 1 GIT_HASH)
endif()

if(GIT_HASH STREQUAL "")
	set(VITA3K_GIT_REV "Development version")
	set(GIT_COUNT 0)
elseif((GIT_REPO STREQUAL "Vita3K") AND ((GIT_BRANCH STREQUAL "master") OR (GIT_BRANCH STREQUAL "HEAD")))
	set(VITA3K_GIT_REV "${GIT_HASH}")
	set(VITA3K_OFFICIAL_UPDATE_BUILD 1)
else()
	set(VITA3K_GIT_REV "${GIT_HASH}-${GIT_REPO}/${GIT_BRANCH}")
endif()

file(WRITE ${CMAKE_BINARY_DIR}/vita3k/config/gitver.h
	"#define APP_VER_HI ${VITA3K_APP_VER_HI}\n"
	"#define APP_VER_MID ${VITA3K_APP_VER_MID}\n"
	"#define APP_VER_LO ${VITA3K_APP_VER_LO}\n"
	"#define APP_NUMBER ${GIT_COUNT}\n"
)

include_directories(${CMAKE_BINARY_DIR}/vita3k/config)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(LINUX TRUE)

	find_package(X11)
	if(X11_FOUND)
		add_compile_definitions(HAVE_X11)
	endif()

	find_package(PkgConfig)
	if(PkgConfig_FOUND)
		pkg_check_modules(WAYLAND wayland-client)
		if(WAYLAND_FOUND)
			add_compile_definitions(HAVE_WAYLAND)
		endif()
	endif()
endif()

get_boost()

include_directories(${Boost_INCLUDE_DIRS})

if (USE_DISCORD_RICH_PRESENCE)
	add_definitions(-DUSE_DISCORD)
endif()

if(BUILD_LIBRETRO)
	add_definitions(-DBUILD_LIBRETRO)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT MSVC)
	add_compile_options(-Wformat -Werror=format-security)
endif()

add_subdirectory(app)
add_subdirectory(audio)
add_subdirectory(camera)
add_subdirectory(input)
add_subdirectory(config)
add_subdirectory(cpu)
add_subdirectory(ctrl)
add_subdirectory(codec)
add_subdirectory(compat)
add_subdirectory(dialog)
add_subdirectory(display)
add_subdirectory(features)
add_subdirectory(glutil)
add_subdirectory(gxm)
add_subdirectory(ime)
add_subdirectory(net)
add_subdirectory(ngs)
add_subdirectory(np)
add_subdirectory(emuenv)
add_subdirectory(http)
add_subdirectory(io)
add_subdirectory(kernel)
add_subdirectory(lang)
add_subdirectory(mem)
add_subdirectory(patch)
add_subdirectory(module)
add_subdirectory(modules)
add_subdirectory(motion)
add_subdirectory(nids)
add_subdirectory(overlay)
add_subdirectory(regmgr)
add_subdirectory(renderer)
add_subdirectory(rtc)
add_subdirectory(shader)
add_subdirectory(threads)
add_subdirectory(touch)
add_subdirectory(util)
add_subdirectory(gdbstub)
add_subdirectory(packages)
add_subdirectory(vkutil)

# The libretro core; the standalone executable, the Android app and the Qt GUI
# are not part of this repository (.upstream-excluded)
add_subdirectory(libretro)
