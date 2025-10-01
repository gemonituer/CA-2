cmake_minimum_required(VERSION 3.20)

project(Lab2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(string_utils STATIC string_utils.c)

set(SOURCES main.c)

add_executable(main ${SOURCES})

target_link_libraries(main string_utils)

target_compile_options(main PRIVATE -Wall -Wextra -O2)
