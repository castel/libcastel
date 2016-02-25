project(libcastel)

cmake_minimum_required(VERSION "2.8")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++14")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/parse/includes")
include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/compile/includes")
include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/runtime/includes")
include_directories(BEFORE "${CMAKE_BINARY_DIR}/includes")

add_subdirectory("parse")
add_subdirectory("compile")
add_subdirectory("microcastel")
add_subdirectory("runtime")
