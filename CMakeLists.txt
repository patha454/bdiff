# CMake version check.
cmake_minimum_required(VERSION 3.13)

# Create the 'bdiff' project.
project(bdiff)

# Use C99 by default.
set(CMAKE_C_STANDARD 99)

# Create the bdiff executable.
add_executable(bdiff)
target_include_directories(bdiff PUBLIC include)
target_sources(bdiff PUBLIC src/bdiff.c)
