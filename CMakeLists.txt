cmake_minimum_required(VERSION 3.5)
project(CPPTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(SOURCE_FILES cpp/other_programs/Main.cpp cpp/programs/DataStructures/List.h cpp/programs/DataStructures/Stack.h cpp/programs/DataStructures/SinglyLinkedList.h cpp/programs/DataStructures/Queue.h cpp/programs/DataStructures/Vector.h cpp/programs/DataStructures/HashTable.h cpp/programs/DataStructures/BinarySearchTree.h cpp/programs/DataStructures/RedBlackTree.h cpp/programs/DP/LongIncSub.h cpp/programs/DataStructures/Graph.h cpp/hackerrank/RedJohnIsBack.cpp cpp/Config.cpp cpp/Config.h)
set(SOURCE_FILES cpp/hackerrank/RedJohnIsBack.cpp cpp/Config.cpp cpp/Config.h)
add_executable(CPPTest ${SOURCE_FILES})