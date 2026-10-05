if(BUILD_LIBRETRO)
    add_library(
        audio
        STATIC
        src/audio.cpp
        src/impl/cubeb_audio.cpp
        src/impl/libretro_audio.cpp)

    target_include_directories(audio PUBLIC include)
    # SDL for the microphone port's stream, as upstream
    target_link_libraries(audio PRIVATE util cubeb kernel SDL3::SDL3)
else()
    add_library(
        audio
        STATIC
        src/audio.cpp
        src/impl/sdl_audio.cpp
        src/impl/cubeb_audio.cpp)

    target_include_directories(audio PUBLIC include)
    target_link_libraries(audio PRIVATE util cubeb SDL3::SDL3)
endif()
