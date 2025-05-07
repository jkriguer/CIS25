cmake_minimum_required(VERSION 3.30)
project(Hangman)

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

# Main executable
add_executable(Hangman
        main.cpp
        ${SOURCES}
)

# GoogleTest Setup
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# Prevent GoogleTest from overriding MSVC settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing support
enable_testing()

# Test executable
add_executable(hangman_tests
        test/hangman_tests.cpp
        ${SOURCES}
)
target_include_directories(hangman_tests PRIVATE include)
target_link_libraries(hangman_tests gtest_main)

# Register tests
include(GoogleTest)
gtest_discover_tests(hangman_tests)
