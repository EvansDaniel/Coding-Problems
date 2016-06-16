/*
//
// Created by daniel on 6/13/16.
//

#ifndef CPPTEST_LINKEDLIST_H
#define CPPTEST_LINKEDLIST_H


#include <iostream>

template<typename T>
class LinkedList {

public:
    // constructors and destructors
    LinkedList();

    LinkedList(const LinkedList<T> &src);

    void swap(LinkedList<T>& other);

    ~LinkedList();

    T &front();

    T &back();

    int size();

    bool empty();

    bool search(T data);

    LinkedList<T>& operator= (LinkedList<T> rhs);

    void pushFront(const T &);

    void pushBack(const T &);

    void popFront();

    void popBack();

    void dump();

private:

     class const_iterator
     {
         public:
         const_iterator( ) : current{ nullptr }
         { }

         const T& operator* ( ) const
         { return retrieve( ); }

         const_iterator & operator++ ( )
         {
             current = current->link;
             return *this;
             }

         const_iterator operator++ ( int )
         {
             const_iterator old = *this;
             ++( *this );
             return old;
             }


         bool operator== ( const const_iterator & rhs ) const
         { return current == rhs.current; }
         bool operator!= ( const const_iterator & rhs ) const
         { return !( *this == rhs ); }

         protected:
         Node *current;

         T & retrieve( ) const
         { return current->data; }

         const_iterator( Node *p ) : current{ p }
         { }

         friend class List<Object>;
         };
    class Node {

        friend class LinkedList<T>;

    private:
        T data;
        Node *link;

    public:
        Node(T d = -1111111, Node *n = nullptr) : data(d), link(n) { }
    };

    Node *head;
    Node *tail;
    int len;
};


// src = list2
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &src) {
    std::cout << "\nCopy constructor has been called.\n\n";
    Node *curr = src.head;
    while (curr) {
        pushBack(curr->data);
        curr = curr->link;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (!this->empty())
        this->popFront();
}


template<typename T>
LinkedList<T>::LinkedList(void) : head(nullptr),
                                  tail(nullptr),
                                  len(0) { }


*/
/**
 * returns lvalue reference to the head's data
 *//*

template<typename T>
T &LinkedList<T>::front() {
    assert(head != nullptr);
    return head->data;
}

template<typename T>
T &LinkedList<T>::back() {
    assert(tail != nullptr);
    return tail->data;
}

template<typename T>
int LinkedList<T>::size() {
    return len;
}

template<typename T>
bool LinkedList<T>::empty() {
    return len == 0;
}

template<typename T>
void LinkedList<T>::pushFront(const T &d) {
    // make the new head point to the old head
    Node *newHead = new Node(d, head);

    if (this->empty()) {
        head = newHead;
        tail = newHead;
    } else {
        head = newHead;
    }
    ++len;
}

template<typename T>
void LinkedList<T>::popFront() {
    assert(head != nullptr);

    Node *oldhead = head;
    if (len == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->link;
    }
    delete oldhead;
    oldhead = nullptr;
    --len;
}

template<typename T>
void LinkedList<T>::popBack() {
    assert(head != nullptr);
    Node *tmp = tail;
    if (len == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        Node *curr = head;
        while (curr->link != tail) {
            curr = curr->link;
        }
        curr->link = nullptr;
        tail = curr;
    }
    delete tmp;
    --len;
}

template<typename T>
bool LinkedList<T>::search(T data) {

}

template<typename T>
void LinkedList<T>::pushBack(const T &d) {

    Node *curr = new Node(d, nullptr);

    if (this->empty())
        head = curr;
    else
        tail->link = curr;

    tail = curr;
    ++len;
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& other)
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(len, other.len);
}

*/
/*template <typename T>
void swap(LinkedList<T>& a, LinkedList<T>& b)
{
    a.swap(b);
}*//*


template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> rhs) {
    std::cout << "operator equals";
//    swap(*this, rhs);
    swap(rhs);
    return *this;
}

template<typename T>
void LinkedList<T>::dump() {
    for (Node *curr = head; curr != nullptr; curr = curr->link) {
        if (curr->link)
            std::cout << "[" << curr->data << "]" << "->";
        else
            std::cout << "[" << curr->data << "]";
    }
    std::cout << "\n";
}

#endif //CPPTEST_LINKEDLIST_H
*/
