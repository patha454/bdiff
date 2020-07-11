# CMake version check.
cmake_minimum_required(VERSION 3.13)

# Create the 'bdiff' project.
project(bdiff)

# Use C99 by default.
set(CMAKE_C_STANDARD 99)

if (MSVC)
    # Disable C11 deprecation warnings.
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Compile as C89 with warnings as errors.
    set(CMAKE_C_FLAGS "-Za -W3 -WX")
endif()

# Create the bdiff executable.
add_executable(bdiff)
target_include_directories(bdiff PUBLIC include)
target_sources(bdiff PUBLIC src/bdiff.c
    src/buffer.c
    src/file.c)
