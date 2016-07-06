cmake_minimum_required(VERSION 3.5)
project(CPPTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES cpp/other_programs/Main.cpp cpp/classes/List.h cpp/classes/Stack.h cpp/classes/SinglyLinkedList.h cpp/classes/Queue.h cpp/classes/Vector.h cpp/classes/HashTable.h cpp/classes/BinarySearchTree.h)
add_executable(CPPTest ${SOURCE_FILES})