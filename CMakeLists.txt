cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(googletest-main)
include_directories(googletest-main/googletest/include)

add_executable(untitled main.cpp test.cpp TritSet.cpp TritSet.h)
target_link_libraries(untitled gtest)