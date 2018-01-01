cmake_minimum_required(VERSION 3.1.0)
project(opengl-demo)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -pedantic")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++ -Wall -Wextra -pedantic")
endif()

file(GLOB_RECURSE opengl-demo_source ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(opengl-demo ${opengl-demo_source})

set(GLFW_BUILD_DOCS FALSE CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES FALSE CACHE BOOL "")
set(GLFW_BUILD_TESTS FALSE CACHE BOOL "")

set(OPTION_BUILD_GPU_TESTS FALSE CACHE BOOL "")
set(OPTION_BUILD_TESTS FALSE CACHE BOOL "")
set(OPTION_BUILD_TOOLS FALSE CACHE BOOL "")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)
target_link_libraries(opengl-demo glfw ${GLFW_LIBRARIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/tdpi)
target_link_libraries(opengl-demo tdpi)
