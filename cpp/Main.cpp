
//
// Created by daniel on 6/13/16.
//
#include <iostream>
#include "SinglyLinkedList.h"

using namespace std;

int main() {


    SSL<int> l;

    l.push_back(7);

//    l.print();

    l.push_front(8);

    l.print();

    cout << endl;
    cout << endl;

    l.erase(l.begin());

//    l.erase(l.begin(),l.end());

    l.push_back(45);
    l.push_front(56);
    l.push_back(23);
    l.pop_front();

    l.print();



}