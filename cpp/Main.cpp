//
// Created by daniel on 6/13/16.
//
#include <assert.h>
#include "LinkedList.h"

int main() {

    LinkedList<int> list;
    assert (list.size() == 0);
    assert (list.empty());

    list.pushFront(1);
    assert (list.size() == 1);
    assert (!list.empty());

    list.pushBack(2);
    list.pushBack(3);

    list.popBack();

    LinkedList<int> list2;

    list2.pushBack(2);
    list2.pushBack(3);

    list2.popBack();

    list.dump();
    list2.dump();


}