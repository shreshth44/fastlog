cmake_minimum_required(VERSION 3.15)
project(FastLog VERSION 0.1.0 LANGUAGES CXX)

# --- Options ---
option(BUILD_BENCHMARKS "Build benchmarks" ON)
option(BUILD_TESTS "Build tests" ON)

# --- Standard Settings ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings
if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Sources ---
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- Executable ---
add_executable(fastlog ${SOURCES})

# --- Includes ---
target_include_directories(fastlog PRIVATE include)

# Threading support
find_package(Threads REQUIRED)
target_link_libraries(fastlog PRIVATE Threads::Threads)
