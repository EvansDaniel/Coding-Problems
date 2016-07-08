//
// Created by daniel on 6/21/16.
//

#include "../classes/BinarySearchTree.h"
#include <typeinfo>

bool isPerfectSquare(int num) {
    if (num == 1) return true;
    for (int divisor = 2; divisor <= num / divisor; ++divisor) {
        if (divisor * divisor == num)
            return true;
    }
    return false;
}

int main() {
    BinarySearchTree<int> tree;
    /*
     *
     */
    tree.insert(0);
    tree.insert(-5);
    tree.insert(5);
    tree.insert(-8);
    tree.insert(-3);
    tree.insert(-7);
    tree.insert(-6);
    // -8, -7, -6, -5, -3, 0, 5
    // median == -5
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

};
