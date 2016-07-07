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

    ~BinarySearchTree() {
        clearTree(root);
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
        TreeNode *node = new TreeNode;
        node->data = data;
        insert(node);
        ++numNodes;
    }
    void inorderPrint() {
        TreeNode *node = root;
        inorderPrint(node);
        node = nullptr;
    }

    void clearTree(TreeNode *root) {
        if (root == nullptr) return;
        clearTree(root->left);
        clearTree(root->right);
        delete root;
        return;
    }

    TreeNode *duplicateNode(TreeNode *node) {
        TreeNode *duplicateNode;
        duplicateNode = new TreeNode();
        *duplicateNode = *node;
        duplicateNode->left = nullptr;
        duplicateNode->right = nullptr;
        return duplicateNode;
    }

    TreeNode *searchTree(T d) {
        TreeNode *temp;
        for (temp = root; temp != nullptr && temp->data != d;) {
            if (d < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        if (temp == nullptr) return nullptr;
        return duplicateNode(temp);
    }

private:
    void inorderPrint(TreeNode *node) {
        if (node != nullptr) {
            inorderPrint(node->left);
            std::cout << node->data << std::endl;
            inorderPrint(node->right);
        }
    }

    void insert(TreeNode *node) {
        TreeNode *back = nullptr;
        TreeNode *temp = root;
        while (temp) {
            back = temp;
            if (node->data > temp->data)
                temp = temp->right;
            else
                temp = temp->left;
        }
        node->parent = back;
        if (!back)
            root = node;
        else if (node->data > back->data)
            back->right = node;
        else
            back->left = node;
    }
};


#endif //CPPTEST_BINARYSEARCHTREE_H
