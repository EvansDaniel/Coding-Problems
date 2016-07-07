//
// Created by daniel on 7/5/16.
//

#ifndef CPPTEST_BINARYSEARCHTREE_H
#define CPPTEST_BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include "Stack.h"

///<

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
    void insert(T data) {
        TreeNode *node = new TreeNode;
        node->data = data;
        insert(node);
        ++numNodes;
    }

    TreeNode *findMax() {
        return findMax(root);
    }

    TreeNode *findMin() {
        return findMin(root);
    }
    void inorderPrint() {
        TreeNode *node = root;
        inorderPrint(node);
        node = nullptr;
    }

    void postorderPrint() {
        TreeNode *node = root;
        postorderPrint(node);
        node = nullptr;
    }

    void preorderPrint() {
        TreeNode *node = root;
        preorderPrint(node);
        node = nullptr;
    }

    // prints inner lefts but not inner rights
    void inorderPrint_i() {
        TreeNode *current = root;
        TreeNode *pre = nullptr;
        while (current != nullptr) {
            if (!current->left) {
                printf(" %d ", current->data);
                current = current->right;
            }
            else {
                /* Find the inorder predecessor of current */
                pre = current->left;
                while (pre->right && pre->right != current)
                    pre = pre->right;

                /* Make current as right child of its inorder predecessor */
                // this is a switch, on the first pass, pre->right will be null, but it is switched to
                // be the successor of pre. On the next pass, pre->right won't be null, so the else is run.
                if (pre->right == nullptr) {
                    pre->right = current;
                    current = current->left;
                }
                else {
                    pre->right = nullptr;
                    printf(" %d ", current->data);
                    current = current->right;
                } /* End of if condition pre->right == NULL */
            } /* End of if condition current->left == NULL*/
        } /* End of while */
    }

    /*int max = findMax()->data;
    TreeNode *temp = root;
    TreeNode *prev = nullptr;
    TreeNode *other = nullptr;
    bool first = false;
    while(true) {
        while (temp) {
            prev = temp;
            temp = temp->left;
        }
        std::cout << prev->data << std::endl;
        if(prev->data == max) break;
        TreeNode* t = prev;
        prev = prev->parent;
        // going back to parent from left
        if(t != t->parent->right) {
            std::cout << prev->data << std::endl;
            temp = prev->right;
        }
        // going back to parent from right
        else {
            prev = prev->parent;
            std::cout << prev->data << std::endl;
            temp = prev->right;
        }
    }*/
    void inorderPrintWithStack() {
        // the stack stores the pointers that point to nodes whose subtrees
        // we *might* need to iterate through and print the nodes of later
        Stack<TreeNode *> s;
        TreeNode *p = root;

        while (p || !s.empty()) {
            // iterates left from either the right or left child of some parent
            while (p) {
                s.push(p);
                p = p->left;
            }
            // save pointer to TreeNode to print later and check its right subtree
            p = s.peek();
            s.pop();
            std::cout << p->data << std::endl;
            // go to the right subtree, while loops will check for nullity
            p = p->right;
        }
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
    // Takes theta(numNodes) time, because obviously we want to print all the nodes
    void inorderPrint(TreeNode *node) {
        if (node != nullptr) {
            inorderPrint(node->left);
            std::cout << node->data << std::endl;
            inorderPrint(node->right);
        }
    }

    void preorderPrint(TreeNode *node) {
        if (node != nullptr) {
            std::cout << node->data << std::endl;
            inorderPrint(node->left);
            inorderPrint(node->right);
        }
    }

    void postorderPrint(TreeNode *node) {
        if (node != nullptr) {
            inorderPrint(node->left);
            inorderPrint(node->right);
            std::cout << node->data << std::endl;
        }
    }

    TreeNode *findMax(TreeNode *root) {
        TreeNode *node = root;
        while (node->right) {
            node = node->right;
        }
        return duplicateNode(node);
    }

    TreeNode *findMin(TreeNode *root) {
        TreeNode *node = root;
        while (node->left) {
            node = node->left;
        }
        return duplicateNode(node);
    }

    // Takes O(lg(n)) time, because we 'search' through the BST, then
    // insert in theta(1) time
    void insert(TreeNode *newNode) {
        TreeNode *back = nullptr;
        TreeNode *temp = root;
        // performs the search for the place to put the node
        while (temp) {
            back = temp;
            if (newNode->data > temp->data)
                temp = temp->right;
            else
                temp = temp->left;
        }
        // sets up the nodes parent pointer, will be nullptr if first node inserted
        newNode->parent = back;
        /*
         * back will be null if temp which first points to the root node is null
         * so if back is null make root point to the new node
         * otherwise check if newNode should be back's left or right child
         */
        if (!back)
            root = newNode;
        else if (newNode->data > back->data)
            back->right = newNode;
        else
            back->left = newNode;
    }
};


#endif //CPPTEST_BINARYSEARCHTREE_H
