//
// Created by daniel on 7/5/16.
//

#ifndef CPPTEST_BINARYSEARCHTREE_H
#define CPPTEST_BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include "Stack.h"
#include <cmath>
#include <math.h>

/**
 *  if you mark a method const,
 *  it means that this will be of type const
 *  MyClass* instead of MyClass*,  which in its turn means that you cannot
 *  change nonstatic data members that are not declared mutable,
 *  , nor can you call any non-const methods.
 */

///<
template<typename T>
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

template<typename T>
/*
 * For all nodes x, if y is in the left subtree of x, key(y) <= key(x)
 * if y is in the right subtree of x, key(y) >= x
 */
class BinarySearchTree {

private:

    TreeNode<T> *root;
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

    bool empty() const {
        return numNodes == 0;
    }
    void insert(T data) {
        TreeNode<T> *node = new TreeNode<T>;
        node->data = data;
        insert(node);
        ++numNodes;
    }

    const TreeNode<T> *findMax() const {
        return findMax(root);
    }

    const TreeNode<T> *findMin() const {
        return findMin(root);
    }

    void inorderPrint() const {
        TreeNode<T> *node = root;
        inorderPrint(node);
        node = nullptr;
    }

    void postorderPrint() const {
        TreeNode<T> *node = root;
        postorderPrint(node);
        node = nullptr;
    }

    void preorderPrint() const {
        TreeNode<T> *node = root;
        preorderPrint(node);
        node = nullptr;
    }

    // prints inner lefts but not inner rights
    void inorderPrintNoStack() const {
        TreeNode<T> *current = root;
        TreeNode<T> *pre = nullptr;
        while (current != nullptr) {
            if (!current->left) {
                printf(" %d ", current->data);
                current = current->right;
            }
            else {
                // Find the inorder predecessor of current
                pre = current->left;
                while (pre->right && pre->right != current)
                    pre = pre->right;

                // Make current as right child of its inorder predecessor
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
                }
            }
        }
    }

    void inorderPrintWithStack() const {
        // the stack stores the pointers that point to nodes whose subtrees
        // we *might* need to iterate through and print the nodes of later
        Stack<TreeNode<T> *> s;
        TreeNode<T> *p = root;

        while (p || !s.empty()) {
            // iterates left from either the right or left child of some parent
            while (p) {
                s.push(p);
                p = p->left;
            }
            // save pointer to TreeNode<T> to print later and check its right subtree
            p = s.peek();
            s.pop();
            std::cout << p->data << std::endl;
            // go to the right subtree, while loops will check for nullity
            p = p->right;
        }
    }

    const TreeNode<T> *searchTree(T d) const {
        TreeNode<T> *temp;
        for (temp = root; temp != nullptr && temp->data != d;) {
            if (d < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        if (temp == nullptr) return nullptr;
        return temp;
    }

    const TreeNode<T> *searchTree_r(T d) const {
        TreeNode<T> *node = root;
        node = searchTree(node, d);
        return node;
    }

    const TreeNode<T> *findTreeWithRank(int rank) const {
        int numNodes = this->numNodes;
        TreeNode<T> *node = root;
    }

    bool isBST() const {
        TreeNode<T> *node = root;
        return isBST(node, findMin()->data, findMax()->data);
    }

    const TreeNode<T> *select(int rank) const {
        if (rank < 0 || rank > numNodes) {
            throw std::invalid_argument
                    ("rank is either negative or greater than the number of nodes in the tree");
        }
        const TreeNode<T> *node = select(root, rank);
        return node;
    }

    int size() {
        TreeNode<T> *node = root;
        int nodes = 0;
        return size(node, nodes);
    }

    int height(const TreeNode<T> *node) const {
        if (node == nullptr) return -1;
        return 1 + std::max(height(node->right), height(node->left));
    }

    // returns the height of the first node whose data == d
    int height(T d) const {
        const TreeNode<T> *node = searchTree(d);
        return height(node);
    }

    int size(T d) const {
        const TreeNode<T> *node = searchTree(d);
//        int nodes = 0;
//        return size(node, nodes);
        return size(node);
    }
private:
    // size ---------------------
    int size(const TreeNode<T> *root, int &nodes) const {
        if (root == this->root)
            return numNodes;
        if (root != nullptr) {
            ++nodes;
            if (root->right) size(root->right, nodes);
            if (root->left) size(root->left, nodes);
        }
        return nodes;
    }

    int size(const TreeNode<T> *root) const {
        if (root == this->root)
            return numNodes;
        if (root == nullptr)
            return 0;
        return (1 + size(root->left) + size(root->right));
    }

    const TreeNode<T> *select(const TreeNode<T> *root, int rank) const {
        if (!root) return nullptr;
        int nodes = 0;
        int t = size(root->left, nodes);
        // remember when we return, we still act with root, not its right or left children
        if (t > rank) return select(root->left, rank);
        else if (t < rank) return select(root->right, rank - t - 1);
        else return root;
    }

    void clearTree(TreeNode<T> *root) {
        if (root == nullptr) return;
        clearTree(root->left);
        clearTree(root->right);
        delete root;
        --numNodes;
        return;
    }

    bool isBST(TreeNode<T> *root, T min, T max) const {
        if (root == nullptr) return true;
        if (root->data < min) return false;
        if (root->data > max) return false;
        return isBST(root->left, min, root->data) && isBST(root->right, root->data, max);
    }

    TreeNode<T> *searchTree(TreeNode<T> *node, T d) const {
        if (node == nullptr || node->data == d) {
            return node;
        }
        if (d > node->data)
            return searchTree(node->right, d);
        else
            return searchTree(node->left, d);
    }
    // Takes theta(numNodes) time, because obviously we want to print all the nodes
    void inorderPrint(TreeNode<T> *node) const {
        if (node != nullptr) {
            inorderPrint(node->left);
            std::cout << node->data << std::endl;
            inorderPrint(node->right);
        }
    }

    void preorderPrint(TreeNode<T> *node) const {
        if (node != nullptr) {
            std::cout << node->data << std::endl;
            inorderPrint(node->left);
            inorderPrint(node->right);
        }
    }

    void postorderPrint(TreeNode<T> *node) const {
        if (node != nullptr) {
            inorderPrint(node->left);
            inorderPrint(node->right);
            std::cout << node->data << std::endl;
        }
    }

    const TreeNode<T> *findMax(TreeNode<T> *root) const {
        TreeNode<T> *node = root;
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    const TreeNode<T> *findMin(TreeNode<T> *root) const {
        TreeNode<T> *node = root;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // Takes O(lg(n)) time, because we 'search' through the BST, then
    // insert in theta(1) time
    void insert(TreeNode<T> *newNode) {
        TreeNode<T> *back = nullptr;
        TreeNode<T> *temp = root;
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
