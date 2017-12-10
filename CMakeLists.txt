cmake_minimum_required(VERSION 3.1.0)
project(opengl-demo)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -pedantic")

file(GLOB_RECURSE opengl-demo_source ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
add_executable(opengl-demo ${opengl-demo_source})