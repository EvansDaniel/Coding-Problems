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
    tree.insert(100);
    tree.insert(50);
    tree.insert(25);
    tree.insert(33);
    tree.insert(75);
    tree.insert(66);
    tree.insert(12);
    tree.insert(85);
    tree.insert(200);
    tree.insert(150);
    tree.insert(125);
    tree.insert(133);
    tree.insert(166);
    tree.insert(199);
    tree.insert(140);
    const TreeNode<int> *a = tree.select(8);
    const TreeNode<int> *b = tree.select(12);
//    printf(" %d %d\n", a->data, b->data);
    a = tree.findLowestCommonAncestor(a, b);
    if (a)
        std::cout << a->data;
};
