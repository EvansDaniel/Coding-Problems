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
    void leftRotate(RBNode<T> *p) {
        if (!p->right) return;
        RBNode<T> *y = p->right;
        p->right = y->left;
        // if y's left child
        if (y->left != nil) {
            y->left->parent = p;
        }
        y->parent = p->parent;
        // x is root
        if (p->parent == nil)
            r = y;
            // x is left child
        else if (p == p->parent->left)
            p->parent->left = y;
            // x is right child
        else
            p->parent->right = y;

        y->left = p;
        p->parent = y;
    }

    /*
     * precondition: x has a left child (not null)
     */
    void rightRotate(RBNode<T> *p) {
        if (!p->left) return;
        RBNode<T> *lc = p->left;
        p->left = lc->right;

        if (lc->right != nil)
            lc->right->parent = p;

        lc->parent = p->parent;
        // p is root
        if (p->parent == nil)
            r = lc;
            // p is left child
        else if (p == p->parent->left)
            p->parent->left = lc;
            // p is right child
        else
            p->parent->right = lc;

        lc->right = p;
        p->parent = lc;
    }
    void insert(T d) {
        RBNode<T> *nn = new RBNode<T>(d);
        RBNode<T> *p = nil;
        RBNode<T> *x = r;
        // how do I know where to put the new node?
        // search for it based on BST property
        while (x != this->nil) {
            p = x;
            if (nn->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        nn->parent = p;
        // if y is root
        if (p == nil)
            r = nn;
            // should nn be y's left or right child?
        else if (nn->data < p->data)
            p->left = nn;
        else
            p->right = nn;
        // what should I do with nn's pointers/color
        nn->left = nil;
        nn->right = nil;
        nn->color = RED;
        fixInsert(nn);
    }

    /**
     * deletes the first node containing the data d from
     * red-black tree while maintaining the red-black properties
     */
    void deleteNode(T data) {
        RBNode<T> *d = searchTree_r(data);
        RBNode<T> *y, *x;
        if (!d) return;

        if (!d->left || !d->right) {
            // d has a null child
            y = d;
        }
        else {
            // y is d's successor
            y = d->right;
            while (y->left)
                y = y->left;
        }

        // x is y's only child
        if (y->left) {
            x = y->left;
        } else {
            x = y->right;
        }

        // remove y from the parent chain
        x->parent = y->parent;
        if (y->parent) if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        else
            r = x;

        if (y != d)
            d->data = y->data;

        if (y->color == BLACK)
            fixDelete(d);

        delete y;
    }

private:

    void transplant(RBNode<T> *p, RBNode<T> *c) {
        if (p->parent == this->nil)
            r = c;
        else if (p == p->parent->left)
            p->parent->left = c;
        else
            p->parent->right = c;
        c->parent = p->parent;
    }
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
        while (nn->parent->color == RED) {

            // CASE A: nn's parent is a left child
            if (nn->parent == nn->parent->parent->left) {
                // nn's parent's sibling
                // CASE 1: nn's uncle is red
                RBNode<T> *u = nn->parent->parent->right;
                // ***UNCLE IS RED AND PARENT LEFT CHILD***
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
                    // ***UNCLE BLACK(or null) AND PARENT LEFT CHILD***
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
                    rightRotate(nn->parent->parent);
                }
            }
                // CASE B: nn's parent is a right child
            else {
                // CASE 1: nn's parent's sibling
                RBNode<T> *u = nn->parent->parent->left;
                // UNCLE IS RED AND PARENT IS RIGHT CHILD
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
                    // UNCLE IS BLACK(or null) AND PARENT IS RIGHT CHILD
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
                    leftRotate(nn->parent->parent);
                }
            }
        }
        // make sure root is black
        r->color = BLACK;
    }

    void fixDelete(RBNode<T> *x) {

        while (x != r && x->color == BLACK) {
            // X IS A LEFT CHILD 
            if (x == x->parent->left) {
                RBNode<T> *uncle = x->parent->right;
                // UNCLE IS RED 
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    uncle = x->parent->right;
                }
                // W'S CHILDREN ARE BLACK 
                if (uncle->left->color == BLACK && uncle->right->color == BLACK) {
                    uncle->color = RED;
                    x = x->parent;
                } else { // 1 OF W'S CHILDREN IS RED 
                    if (uncle->right->color == BLACK) {
                        uncle->left->color = BLACK;
                        uncle->color = RED;
                        rightRotate(uncle);
                        uncle = x->parent->right;
                    }
                    uncle->color = x->parent->color;
                    x->parent->color = BLACK;
                    uncle->right->color = BLACK;
                    leftRotate(x->parent);
                    x = r;
                }
                // X IS A RIGHT CHILD
            } else {
                RBNode<T> *uncle = x->parent->left;
                // UNCLE IS RED 
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    uncle = x->parent->left;
                }
                // W'S CHILDREN ARE BLACK 
                if (uncle->right->color == BLACK && uncle->left->color == BLACK) {
                    uncle->color = RED;
                    x = x->parent;
                } else {
                    if (uncle->left->color == BLACK) {
                        uncle->right->color = BLACK;
                        uncle->color = RED;
                        leftRotate(uncle);
                        uncle = x->parent->left;
                    }
                    uncle->color = x->parent->color;
                    x->parent->color = BLACK;
                    uncle->left->color = BLACK;
                    rightRotate(x->parent);
                    x = r;
                }
            }
        }
        x->color = BLACK;
    }
};


#endif //CPPTEST_REDBLACKTREE_H
