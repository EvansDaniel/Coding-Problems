
//
// Created by daniel on 6/13/16.
//
#include <iostream>
#include "List.h"

using namespace std;

int main() {

    List<int> list;

    list.push_back(56);  // good
    list.push_front(34); // good

    List<int> list2;
    list2.push_back(3922);

    list = list2;

    for (List<int>::iterator itr = list.begin(); itr != list.end(); ++itr) {
        cout << *itr << endl;
    }



}