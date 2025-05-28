cmake_minimum_required(VERSION 3.10)
project(ReverbAmplifier)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(
    external/imgui
    external/portaudio/include
    external/libsndfile/include
)

# Add your source files here

add_executable(ReverbAmplifier
    src/main.cpp
    src/audio/loader.cpp
    src/audio/reverb.cpp
    src/audio/playback.cpp
    src/gui/imgui_gui.cpp
)

# Link libraries
target_link_libraries(ReverbAmplifier
    portaudio
    sndfile
    glfw
    opengl32
)