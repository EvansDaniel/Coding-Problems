//
// Created by daniel on 7/5/16.
//

#ifndef CPPTEST_BINARYSEARCHTREE_H
#define CPPTEST_BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include "Stack.h"
#include "Vector.h"
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <random>
#include <array>

/**
 *  if you mark a method const,
 *  it means that this will be of type const
 *  MyClass* instead of MyClass*,  which in its turn means that you cannot
 *  change nonstatic data members that are not declared mutable,
 *  , nor can you call any non-const methods.
 */

///<
// TODO: ADD DUPLICATE NODE PRIVATE METHOD TO PREVENT MANIPULATION TO TREE
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
        this->root = nullptr;
        this->numNodes = 0;
        TreeNode<T> *temp = rhs.root;
        traversal(temp);
        temp = nullptr;
    }

    void traversal(TreeNode<T> *root) {
        if (!root)
            return;
        insert(root->data);
        traversal(root->left);
        traversal(root->right);
    }

    ~BinarySearchTree() {
        clearTree(root);
    }

    /*
    // naive implementation of copy-swap idiom
    BinarySearchTree &operator=(const BinarySearchTree &rhs) { // rhs is reference to src, even if src is an rvalue
        BinarySearchTree copy = rhs; // copy construction of rhs does the hard work
        swap(*this, copy);  // swap this's resources for copy's
        return *this; // our (old) resources get destroyed with copy
    }
     */
    // pre c++11, if compiler implements copy elision and rhs is rvalue,
    // compiler will just move the source into rhs rather than copying (worst
    // case is that the compiler must copy it anyway, which is best case in
    // naive implementation); however, above where we pass by const reference
    // and explicitly copy, the compiler does not have the opportunity to optimize
    // away the copy into rhs. In c++11, the move assignment operator is called
    // explicitly by compiler when passing an rvalue, but this mode of
    // thought is still useful to think about
    BinarySearchTree &operator=(BinarySearchTree rhs) {
        swap(*this, rhs);
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
        if (data == nullptr) return;
        TreeNode<T> *node = new TreeNode<T>;
        node->data = data;
        insert(node);
        ++numNodes;
    }

    TreeNode<T> *findMax() const {
        if (!root) return nullptr;
        return findMax(root);
    }

    TreeNode<T> *findMin() const {
        if (!root) return nullptr;
        return findMin(root);
    }

    void inorderPrint() const {
        if (!root) return;
        TreeNode<T> *node = root;
        inorderPrint(node);
        node = nullptr;
    }

    void postorderPrint() const {
        if (!root) return;
        TreeNode<T> *node = root;
        postorderPrint(node);
        node = nullptr;
    }

    void preorderPrint() const {
        if (!root) return;
        TreeNode<T> *node = root;
        preorderPrint(node);
        node = nullptr;
    }

    // prints inner lefts but not inner rights
    void inorderPrintNoStack() const {
        if (!root) return;
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
        if (!root) return;
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

    bool containsNode(T d) const {
        if (d == nullptr) return false;
        TreeNode<T> *temp = nullptr;
        for (temp = root; temp != nullptr && temp->data != d;) {
            if (d < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return temp != nullptr;
    }

    const TreeNode<T> *searchTree_r(T d) const {
        if (!root || d == nullptr) return nullptr;
        TreeNode<T> *node = root;
        return searchTree(node, d);
    }

    bool isBST() const {
        // empty BST is a BST
        if (!root) return true;
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
        TreeNode<T> *node = root; // root nullity checked in in size() helper
        int nodes = 0;
        return size(node, nodes);
    }

    int height(const TreeNode<T> *node) const {
        if (node == nullptr) return -1;
        return 1 + std::max(height(node->right), height(node->left));
    }

    // returns the height of the first node whose data == d
    int height(T d) const {
        if (d == nullptr) return -1;
        const TreeNode<T> *node = searchTree(d);
        return height(node);
    }

    int size(T d) const {
        const TreeNode<T> *node = searchTree(d);
        return size(node);
    }

    // gets rvalue of the median of the tree
    T getTreeMedian() const {
        if (numNodes % 2 == 0)
            return select(numNodes / 2 - 1);
        else
            return select(numNodes / 2);
    }

    // beginnings of a balance tree method
    const TreeNode<T> *createBalancedTree(std::vector<T> v) {
        std::sort(std::begin(v), std::end(v));
        return balanceTreeHelper(v, v.begin(), v.end(), nullptr);
    }

    TreeNode<T> *predecessor(TreeNode<T> *node) {
        if (node == nullptr) return nullptr;
        if (node->left)
            return findMax(node->left);
        TreeNode<T> *nodeParent = node->parent;
        while (nodeParent && nodeParent->left == node) {
            node = nodeParent;
            nodeParent = nodeParent->parent;
        }
        return nodeParent;
    }

    TreeNode<T> *successor(TreeNode<T> *node) {
        if (node == nullptr) return nullptr;
        if (node->right) {
            return findMin(node->right);
        }
        TreeNode<T> *nodeParent = node->parent;
        // while ... and node is the right child of parent
        while (nodeParent != nullptr && node == nodeParent->right) {
            node = nodeParent;
            nodeParent = nodeParent->parent;
        }
        return nodeParent;
    }

    TreeNode<T> *findMinRecursive() {
        if (root == nullptr) return nullptr;
        TreeNode<T> *node = root;
        return findMin_r(node);
    }

    TreeNode<T> *findMaxRecursive() {
        if (root == nullptr) return nullptr;
        TreeNode<T> *node = root;
        return findMax_r(node);
    }

    /**
     * Precondition: a and b are non-null nodes in the tree
     */
    const TreeNode<T> *findLowestCommonAncestor(const TreeNode<T> *a, const TreeNode<T> *b) {
        if (!root || !a || !b) return nullptr;
        TreeNode<T> *ancestor = root;
        while (ancestor) {
            // if ancestor > both a and b
            if (ancestor->data > a->data && ancestor->data > b->data)
                ancestor = ancestor->left;
                // if ancestor < both a and b
            else if (ancestor->data < a->data && ancestor->data < b->data)
                ancestor = ancestor->right;
                // we found LCA so break
            else
                break;
        }
        // could be null if while is skipped
        return ancestor;
    }

    bool deleteNode(T data) {
        if (data == nullptr) return false;
        // we must find the node first
        TreeNode<T> *delNode = searchTree(this->root, data);
        // check if we found a node
        if (delNode) {
            if (!delNode->left)
                transplant(delNode, delNode->right);
            else if (!delNode->right)
                transplant(delNode, delNode->left);
            else { // delNode has 2 children
                // find delNode's successor
                TreeNode<T> *y = findMin(delNode->right);
                // if y != delNode->right
                if (y->parent != delNode) {
                    // make y's parent's left pointer point to what y->right points to
                    transplant(y, y->right);
                    // y is taking the place of delNode
                    y->right = delNode->right;
                    y->right->parent = y;
                }
                // make delNode's parent's left or right point to y
                transplant(delNode, y);
                // copy delNode's left pointer to maintain the state of its left subtree
                y->left = delNode->left;
                y->left->parent = y;
            }
            delete delNode;
        }
        return false;
    }

    TreeNode<T> *LCA_r(const TreeNode<T> *a, const TreeNode<T> *b) {
        if (!a || !b) return nullptr;
        TreeNode<T> *node = root;
        return LCAHelper_r(node, a, b);
    }

    /*
    template<typename It>
    void quicksort(It lowerIt, It upperIt) {
        auto size = std::distance(lowerIt, upperIt);
        std::cout << size << std::endl;
        if(size > 1) {
            auto p = std::prev(upperIt);
            std::swap(*std::next(lowerIt, size/2), *p);
            auto mid = std::partition(lowerIt, p, [p](decltype(*p) v) { return v < *p; });
            std::swap(*mid, *p);
            // the element at index mid is considered sorted, thus we don't
            // include it in the recursions
            quicksort(lowerIt, mid);
            quicksort(std::next(mid), upperIt);
        }
    }
    */

protected:
    /**
     * switches u->parent's right or left pointer to point
     * to v, or if u is the root, makes root point at v
     */
    void transplant(TreeNode<T> *p, TreeNode<T> *c) {
        if (p == nullptr) return;
        // u is the root
        if (p->parent == nullptr)
            root = c;
            // if u is a left child
        else if (p == p->parent->left)
            p->parent->left = c;
            // if u is a right child
        else
            p->parent->right = c;
        // c might be null
        if (c != nullptr) {
            c->parent = p->parent;
        }
    }

    /**
     * recursive helper for finding the lowest common ancestor
     * of two nodes (a and b)
     */
    TreeNode<T> *LCAHelper_r(TreeNode<T> *current, const TreeNode<T> *a, const TreeNode<T> *b) {
        if (!current) return nullptr;
        // a->data and b->data < current-> data, look in current->left subtree for LCA
        if (current->data > a->data && current->data > b->data)
            return LCAHelper_r(current->left, a, b);

        // a->data and b->data > current-> data, look in current->right subtree for LCA
        if (current->data < a->data && current->data < b->data)
            return LCAHelper_r(current->right, a, b);

        return current;
    }
    // for sorted containers, returns the value of median element
    template<typename Iterator>
    long getMedian(Iterator begin,
                   Iterator end) const {
        long dist = std::distance(begin, end);
        if (dist % 2 == 0)
            return dist / 2 - 1;
        else
            return dist / 2;
    }

    friend void swap(BinarySearchTree &first, BinarySearchTree &second) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two programs,
        // the two programs are effectively swapped
        swap(first.root, second.root);
        swap(first.numNodes, second.numNodes);
    }

    // Takes theta(numNodes) time, because obviously we want to print all the nodes
    void inorderPrint(const TreeNode<T> *node) const {
        if (node != nullptr) {
            inorderPrint(node->left);
            std::cout << node->data << std::endl;
            inorderPrint(node->right);
        }
    }

    // v must have no duplicates
    // TODO: fix this
    const TreeNode<T> *balanceTreeHelper(const std::vector<T> &v,
                                         typename std::vector<T>::const_iterator begin,
                                         typename std::vector<T>::const_iterator end,
                                         TreeNode<T> *parent) {

        TreeNode<T> *node = nullptr;
        if (begin != end) {
            long median = getMedian(begin, end);
            std::cout << median << " ";
            node = new TreeNode<T>(v.at((unsigned long) median), parent);
            if (node->parent) {
                if (node->data < node->parent->data) {
                    node->parent->left = node;
                }
                else {
                    node->parent->right = node;
                }
            }
            balanceTreeHelper(v, v.begin(), v.begin() + median, node);
            balanceTreeHelper(v, v.begin() + median + 1, v.end(), node);
        }
        return node;
    }
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
        if (root->left)
            clearTree(root->left);
        if (root->right)
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

    TreeNode<T> *findMax(TreeNode<T> *root) const {
        TreeNode<T> *node = root;
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    TreeNode<T> *findMin(TreeNode<T> *root) const {
        TreeNode<T> *node = root;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    TreeNode<T> *findMin_r(TreeNode<T> *root) const {
        if (!root) return nullptr;
        if (root->left)
            return findMin_r(root->left);
        return root;
    }

    TreeNode<T> *findMax_r(TreeNode<T> *root) const {
        if (!root) return nullptr;
        if (root->right)
            return findMax_r(root->right);
        return root;
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
