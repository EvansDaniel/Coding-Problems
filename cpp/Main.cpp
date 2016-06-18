
//
// Created by daniel on 6/13/16.
//
#include <iostream>
#include "Stack.h"

using namespace std;

int main() {

    Stack<int> stack;

    stack.push(45);
    stack.push(34);
    stack.push(32323);
    cout << stack.peek() << endl;
    cout << stack.pop() << endl;

    while (!stack.empty())
        stack.pop();

    cout << stack.empty() << endl;


/*    *//**
     * push_back
     * copy ctor
     * copy-assignment
     * pop_front
     * move ctor
     * move assignment operator needs work
     * everything else is good
     *//*


    SSL<int> l;

    l.print();

    l.push_back(56);

    SSL<int> l2 = l;

    l2.print();

    SSL<int> l3;

    l3.push_back(45);

    l3 = l2;

    l3.print();

    SSL<int> ssl{SSL<int>(l3)};*/





}