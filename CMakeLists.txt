cmake_minimum_required(VERSION 3.3)
project(YaCourse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp graph.cpp graph.h)
add_executable(YaCourse ${SOURCE_FILES})

include_directories("Packages")