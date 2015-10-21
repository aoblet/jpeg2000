cmake_minimum_required(VERSION 3.3)
project(jpeg2000)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(include)

set(SOURCE_FILES main.cpp src/filters.cpp include/filters.hpp)
add_executable(jpeg2000 ${SOURCE_FILES})