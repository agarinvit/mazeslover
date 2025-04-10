cmake_minimum_required(VERSION 3.29)
project(untitled42)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled42 main.cpp
        visualize.cpp
        node.cpp
        maze.cpp
        algorithms.cpp)

add_compile_options(-ftime-trace)
