//
// Created by daniel on 7/5/16.
//

#ifndef CPPTEST_BINARYSEARCHTREE_H
#define CPPTEST_BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>

template<typename T>
/*
 * For all nodes x, if y is in the left subtree of x, key(y) <= key(x)
 * if y is in the right subtree of x, key(y) >= x
 */
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
    BinarySearchTree() {
        this->root = nullptr;
        this->numNodes = 0;
    }
    BinarySearchTree(const BinarySearchTree &rhs) {
        // deep copy of rhs
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs) {
        std::swap(numNodes, rhs.numNodes);
        std::swap(root, rhs.root);
        return *this;
    }

    BinarySearchTree(BinarySearchTree &&rhs)
            : root{rhs.root}, numNodes{rhs.numNodes} {
        rhs.numNodes = 0;
        rhs.root = nullptr;
    }

    bool empty() {
        return numNodes == 0;
    }

    T findMin() {
        TreeNode *node;
        for (node = root; node->left != nullptr; node = node->left);
        return node->data;
    }

    void insert(T data) {
        TreeNode *node = root;
        insert(node, data);
        ++numNodes;
    }
    void inorderPrint() {
        TreeNode *node = root;
        inorderPrint(node);
        node = nullptr;
    }

private:
    void inorderPrint(TreeNode *node) {
        if (node != nullptr) {
            inorderPrint(node->left);
            std::cout << node->data << std::endl;
            inorderPrint(node->right);
        }
    }

    void insert(TreeNode *node, T data) {
        if (node == nullptr) {
            node = new TreeNode;
            node->data = data;
            return;
        }
        else if (data >= node->data && node->right == nullptr) {
            node->right = new TreeNode;
            node->right->data = data;
        }
        else if (data <= node->data && node->left == nullptr) {
            node->left = new TreeNode;
            node->left->data = data;
        }
        else if (data >= node->data && data <= node->right->data) {
            TreeNode *temp = node->right;
            node->right = new TreeNode;
            node->right->data = data;
            // definitely aren't balancing this tree right now
            node->right->right = temp;
        }
        else if (data <= node->data && data >= node->left->data) {
            TreeNode *temp = node->left;
            node->left = new TreeNode;
            node->left->data = data;
            // definitely aren't balancing this tree right now
            node->left->left = temp;
        }
        else {
            if (data >= node->data)
                insert(node->right, data);
            if (data <= node->data)
                insert(node->left, data);
        }
    }
};


#endif //CPPTEST_BINARYSEARCHTREE_H
