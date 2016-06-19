
//
// Created by daniel on 6/13/16.
//
#include <iostream>
#include "Vector.h"

using namespace std;

int main() {

    Vector<int> v;
    v.push_back(45);
    v.push_back(34);
    v.resize(30);
//    v.print();


    // calls the move constructor
    Vector<int> vector = std::move(v);
    /*
     * v.back() = 30;
     * the above method is invalid because
     * back() returns a const lvalue reference
     */
    for (auto itr = vector.begin(); itr != vector.end();)
        cout << *itr++ << endl;

}