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
add_compile_definitions(LOGS_DIR="${CMAKE_SOURCE_DIR}/logs")

# Main executable
add_executable(SAM-I-AM
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
add_executable(sam_tests
        test/sam_tests.cpp
        ${SOURCES}
)
target_include_directories(sam_tests PRIVATE include)
target_link_libraries(sam_tests gtest_main)

# Register tests
include(GoogleTest)
gtest_discover_tests(sam_tests)
