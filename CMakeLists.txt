cmake_minimum_required(VERSION 3.5)
project(CPPTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES Main.cpp LinkedList.h)
add_executable(CPPTest ${SOURCE_FILES})