
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
    /*
     * v.back() = 30;
     * the above method is invalid because
     * back() returns a const lvalue reference
     */
    for (auto itr = v.begin(); itr != v.end();)
        cout << *itr++ << endl;


}