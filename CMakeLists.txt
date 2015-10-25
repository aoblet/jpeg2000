cmake_minimum_required(VERSION 3.3)
project(jpeg2000)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(include)
set(SOURCE_FILES main.cpp src/filters.cpp include/filters.hpp src/Signal1D.cpp include/Signal1D.hpp src/test.cpp include/test.hpp)

FIND_PACKAGE( Boost 1.44 COMPONENTS system filesystem REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(jpeg2000 ${SOURCE_FILES})
TARGET_LINK_LIBRARIES( jpeg2000 ${Boost_LIBRARIES} )
