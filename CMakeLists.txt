cmake_minimum_required(VERSION 2.8)
project(jpeg2000)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE( Boost 1.44 COMPONENTS system filesystem REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
include_directories(include)

file(GLOB_RECURSE HEADER_FILES src/*.hpp include/*.hpp) # get all headers
file(GLOB_RECURSE SRC_FILES src/*.cpp) # get all sources files

add_executable(jpeg2000 main.cpp ${SRC_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES( jpeg2000 ${Boost_LIBRARIES} )
