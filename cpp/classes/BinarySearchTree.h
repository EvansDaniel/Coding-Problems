//
// Created by daniel on 7/5/16.
//

#ifndef CPPTEST_BINARYSEARCHTREE_H
#define CPPTEST_BINARYSEARCHTREE_H

#include <algorithm>

template<typename T>
class BinarySearchTree {

private:

    struct TreeNode {
        T data;
        TreeNode *left;
        TreeNode *right;
        TreeNode *parent;

        // constructor for the TreeNode struct, T {} initializes d with default constructor of T
        TreeNode(const T &d = T{}, TreeNode *p = nullptr,
                 TreeNode *left = nullptr, TreeNode *right = nullptr)
                : data{d}, parent{p}, left{left}, right{right} { }

        TreeNode(T &&d, TreeNode *p = nullptr, TreeNode *l = nullptr, TreeNode *r = nullptr)
                : data{std::move(d)}, parent{p}, left{l}, right{r} { }
    };

    TreeNode *root;
    int numNodes;

public:
    BinarySearchTree(T data) {
        this->root = new TreeNode;
        this->root->data = data;
        this->root->left = nullptr;
        this->root->right = nullptr;
        this->numNodes = 1;
    }

    BinarySearchTree() {
        this->root = nullptr;
        this->root->left = nullptr;
        this->root->right = nullptr;
        this->numNodes = 1;
    }

    BinarySearchTree(const BinarySearchTree &rhs) {
        // deep copy of rhs
    }

    BinarySearchTree(BinarySearchTree &&rhs) {
        // use std::move()
    }

    BinarySearchTree
    void inorderPrint() {
        TreeNode *node = root;

    }

};

#endif //CPPTEST_BINARYSEARCHTREE_H
