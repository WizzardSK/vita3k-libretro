add_library(vita3k_libretro SHARED
	# app loading and launch, shared with the standalone (app links it)
	${CMAKE_CURRENT_SOURCE_DIR}/../interface.cpp
	libretro_vita3k.cpp
	libretro_input.cpp
	libretro_installer.cpp
	libretro_lazy_pkg.cpp
	libretro_vfs.cpp
	libretro_log.cpp
	libretro_game_loader.cpp
	libretro_accounts.cpp
)

target_include_directories(vita3k_libretro PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/external/concurrentqueue
	${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Link against Vita3K static libraries (excluding gui and gdbstub)
target_link_libraries(vita3k_libretro PRIVATE
	app
	audio
	camera
	config
	cppcommon
	ctrl
	compat
	dialog
	display
	gdbstub
	glad
	ime
	lang
	overlay
	gxm
	io
	miniz
	modules
	motion
	np
	packages
	patch
	psvpfsparser
	renderer
	shader
	touch
	util
	pugixml::pugixml
)

# Output name: vita3k_libretro.dll / vita3k_libretro.so / vita3k_libretro.dylib
set_target_properties(vita3k_libretro PROPERTIES
	PREFIX ""
	OUTPUT_NAME "vita3k_libretro"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(WIN32)
	target_link_libraries(vita3k_libretro PRIVATE Version)
	if(MSVC)
		target_link_options(vita3k_libretro PRIVATE
			"/MAP:$<TARGET_FILE_DIR:vita3k_libretro>/vita3k_libretro.map"
			"/MAPINFO:EXPORTS")
	endif()
endif()

if(LINUX)
	target_link_libraries(vita3k_libretro PRIVATE -static-libgcc -static-libstdc++)
	# Only the libretro API is exported, and the core's own calls bind to its own code: the
	# C++ runtime linked in above was otherwise exported too, and its calls went to the
	# frontend's libstdc++ where that was loaded first - std::cout crashed in rif2zrif on a
	# system with GCC 16's (Shoegzer, #1)
	target_link_options(vita3k_libretro PRIVATE
		"-Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/link.T"
		"-Wl,-Bsymbolic"
		"-Wl,--exclude-libs,ALL")
	set_property(TARGET vita3k_libretro APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/link.T")
endif()

# data/, the built-in shaders and the dialog icons are compiled into the core and
# unpacked into system/vita3k by it (libretro_vita3k.cpp); the languages are
# compiled in too (lang/, from i18n/)
include(${CMAKE_CURRENT_SOURCE_DIR}/embed_system_files.cmake)
vita3k_libretro_embed_files(${CMAKE_CURRENT_BINARY_DIR}/libretro_bundled_files.cpp)
target_sources(vita3k_libretro PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/libretro_bundled_files.cpp)

# libretro_lazy_pkg.cpp decrypts the PKG layer itself, with OpenSSL; on macOS
# the headers are those of the OpenSSL external/ finds or builds, not the
# system's. Through external/'s crypto target: OpenSSL::Crypto, an imported
# target, is seen only in the directory that found it
target_link_libraries(vita3k_libretro PRIVATE crypto)

# The commit of this repository the core is built from, for the log: testers'
# logs then say which build they come from
execute_process(
	COMMAND git rev-parse --short=8 HEAD
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	OUTPUT_VARIABLE VITA3K_LIBRETRO_COMMIT
	OUTPUT_STRIP_TRAILING_WHITESPACE
	ERROR_QUIET)
if(NOT VITA3K_LIBRETRO_COMMIT)
	set(VITA3K_LIBRETRO_COMMIT "unknown")
endif()
set_source_files_properties(libretro_vita3k.cpp PROPERTIES
	COMPILE_DEFINITIONS "VITA3K_LIBRETRO_COMMIT=\"${VITA3K_LIBRETRO_COMMIT}\"")
