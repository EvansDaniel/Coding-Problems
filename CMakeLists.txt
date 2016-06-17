cmake_minimum_required(VERSION 3.5)
project(CPPTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES cpp/Main.cpp cpp/LinkedList.h cpp/List.h cpp/Stack.h cpp/SinglyLinkedList.h)
add_executable(CPPTest ${SOURCE_FILES})