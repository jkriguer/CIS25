cmake_minimum_required(VERSION 3.30)
project(SAM-I-AM)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Use static runtime for Visual Studio on Windows
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Include headers from include/
include_directories(include)

# Glob (thanks light!)
file(GLOB SOURCES "src/*.cpp")

# path
add_compile_definitions(SCENARIOS_DIR="${CMAKE_SOURCE_DIR}/scenarios")

# Main executable
add_executable(SAM-I-AM
        main.cpp
        ${SOURCES}
)