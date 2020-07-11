# CMake version check.
cmake_minimum_required(VERSION 3.5)

# Create the 'bdiff' project.
project(bdiff)

# Use C99 by default.
set(CMAKE_C_STANDARD 90)

cmake_policy(SET CMP0076 NEW)

# Create the bdiff executable.
add_executable(bdiff)

target_include_directories(bdiff PUBLIC include)

target_sources(bdiff PUBLIC src/bdiff.c
    src/buffer.c
    src/file.c)

# Set compiler options.
if (MSVC)
    # Disable C11 deprecation warnings.
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Compile as C89 with warnings as errors.
    target_compile_options(bdiff PRIVATE "-Za" "-W3" "-WX")
elseif (CMAKE_C_COMPILER_ID STREQUAL "GCC" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    # Compile as C89 with strict warnings as errors.
    target_compile_options(bdiff PRIVATE "-W" "-Wall" "-Wpedantic" "-Wextra" "-Werror")
endif()
