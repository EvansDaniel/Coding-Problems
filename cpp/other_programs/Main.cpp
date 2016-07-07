//
// Created by daniel on 6/21/16.
//

#include "../classes/BinarySearchTree.h"

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
    tree.insert(0);
    tree.insert(-5);
    tree.insert(5);
    tree.insert(-8);
    tree.insert(-3);
    tree.insert(-7);
    tree.insert(-6);
    tree.preorderPrint();
};
