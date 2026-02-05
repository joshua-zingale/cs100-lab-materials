cmake_minimum_required(VERSION 3.5)
project(ansi)

SET (CMAKE_CXX_STANDARD 20)

# add_library(ansi STATIC)


add_executable(interactive-ansi
    src/interactive-ansi.cpp
    src/ansi.cpp)

target_include_directories(interactive-ansi PRIVATE src/)


