//
// Created by daniel on 7/10/16.
//

#ifndef CPPTEST_REDBLACKTREE_H
#define CPPTEST_REDBLACKTREE_H

#include <algorithm>
#include <iostream>
#include "Stack.h"
#include "Vector.h"
#include "BinarySearchTree.h"
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
template<typename T>
struct RBNode : TreeNode<T> {
    RBNode<T> *left;
    RBNode<T> *right;
    RBNode<T> *parent;
    int color;

    // constructor for the TreeNode struct, T {} initializes d with default constructor of T
    RBNode(const T &d = T{}, RBNode *p = nullptr,
           RBNode *left = nullptr, RBNode *right = nullptr, int color = 0)
            : TreeNode(d, p, left, right), color{color} { }

    RBNode(T &&d, RBNode *p = nullptr, RBNode *l = nullptr, RBNode *r = nullptr,
           int color = 0)
            : TreeNode(d, p, left, right), color{color} { }
};

template<typename T>
/*
 * BST property:
 * For all nodes x, if y is in the left subtree of x, key(y) <= key(x)
 * if y is in the right subtree of x, key(y) >= x
 */
class RedBlackTree : public BinarySearchTree {

private:
    RBNode<T> *r;
    int numNodes;
    // sentinel node for nullptr child leaf nodes
    RBNode<T> *nil;
    const static int RED = 0;
    const static int BLACK = 1;

public:
    RedBlackTree() {
        nil = new RBNode<T>;
        nil->color = BLACK;
        numNodes = 0;
        // on first insert must set r->parent to nil
        r = nil;
    }

    /*
     * precondition: x has a right child (not null)
     */
    void leftRotate(RBNode<T> *x) {
        RBNode<T> *y = x->right;
        x->right = y->left;
        // if y's left child
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        // x is root
        if (x->parent == nil)
            r = y;
            // x is left child
        else if (x == x->parent->left)
            x->parent->left = y;
            // x is right child
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    /*
     * precondition: x has a left child (not null)
     */
    void rightRotate(RBNode<T> *x) {
        RBNode<T> *y = x->left;
        x->left = y->right;
        // y has left child (not null)
        if (y->right != nil)
            y->right->parent = x;

        y->parent = x->parent;
        // x is root
        if (x->parent == nil)
            r = y;
            // x is left child
        else if (x == x->parent->left)
            x->parent->left = y;
            // x is right child
        else
            x->parent->right = y;

        y->right = x;
        x->parent = y;
    }

    void insert(T d) {
        RBNode<T> *nn = new RBNode<T>(d);
        RBNode<T> *y = nil;
        RBNode<T> *x = r;
        // search for place to put nn (new_node)
        while (x != this->nil) {
            y = x;
            if (nn->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        nn->parent = y;
        // if y is root
        if (y == nil)
            r = nn;
            // nn should be y's left child
        else if (nn->data < y->data)
            y->left = nn;
            // nn should be y's right child
        else
            y->right = nn;
        // set nn's children and color
        nn->left = nil;
        nn->right = nil;
        nn->color = RED;
        // rebalance tree
        fixInsert(nn);
    }

private:
    void fixInsert(RBNode<T> *nn) {
        /**
         * Loop Invariant at the start of each iteration:
         *      1. Node nn is red
         *      2. If nn->parent is the root, then nn->parent is black
         *         (this is also the stopping condition)
         *      3. If the tree violates any of the RB tree props, then
         *         it violates at most one of them, and the violation
         *         is b/c nn is the root and is red. If the tree violates
         *         prop 4 (red node cannot have red children), it is b/c
         *         both nn and nn->parent are red
         */
        // checks for a double red violation
        while (nn != r && nn->parent->color == RED) {

            // CASE A: nn's parent is a left child
            if (nn->parent == nn->parent->parent->left) {
                // nn's parent's sibling
                // CASE 1: nn's uncle is red
                RBNode<T> *u = nn->parent->parent->right;
                // **UNCLE IS RED**
                if (u && u->color == RED) {
                    // change parent black
                    nn->parent->color = BLACK;
                    // change uncle to black
                    u->color = BLACK;
                    // change grandparent red
                    nn->parent->parent->color = RED;
                    // make nn its grandparent
                    nn = nn->parent->parent;
                }
                else {
                    // CASE 2: nn is a right child of its parent
                    if (nn == nn->parent->right) {
                        nn = nn->parent;
                        leftRotate(nn);
                    }
                    // CASE 3: nn is left child of its parent
                    nn->parent->color = BLACK;
                    // change nn's grandparent red
                    nn->parent->parent->color = RED;
                    rightRotate(nn);
                }
            }
                // CASE B: nn's parent is a right child
            else {
                // CASE 1: nn's parent's sibling
                RBNode<T> *u = nn->parent->parent->left;
                // sibling of nn's parent is red
                if (u && u->color == RED) {
                    // change parent black
                    nn->parent->color = BLACK;
                    // change uncle black
                    u->color = BLACK;
                    // change grandparent red
                    nn->parent->parent->color = RED;
                    // make nn its grandparent
                    nn = nn->parent->parent;
                }
                else {
                    // CASE 2: nn is a left child of its parent
                    if (nn == nn->parent->left) {
                        nn = nn->parent;
                        rightRotate(nn);
                    }
                    // CASE 3: nn is a right child of its parent
                    nn->parent->color = BLACK;
                    // make nn's grandparent red
                    nn->parent->parent->color = RED;
                    leftRotate(nn);
                }
            }
        }
        // make sure root is black
        r->color = BLACK;
    }
};

#endif //CPPTEST_REDBLACKTREE_H
