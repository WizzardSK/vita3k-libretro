add_library(vita3k_libretro SHARED
	# app loading and launch, shared with the standalone (app links it)
	${CMAKE_CURRENT_SOURCE_DIR}/../interface.cpp
	libretro_vita3k.cpp
	libretro_input.cpp
	libretro_installer.cpp
	libretro_lazy_pkg.cpp
	libretro_log.cpp
	libretro_game_loader.cpp
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
endif()

# Copy data and the built-in shaders to the output dir; the languages are
# compiled in (lang/, from i18n/)
add_custom_command(
	TARGET vita3k_libretro
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/../../data" "$<TARGET_FILE_DIR:vita3k_libretro>/data"
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/../shaders-builtin" "$<TARGET_FILE_DIR:vita3k_libretro>/shaders-builtin"
)
