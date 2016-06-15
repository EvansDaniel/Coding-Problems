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

    ~LinkedList();

    T &front();

    T &back();

    int size();

    bool empty();

    bool search(T data);

    LinkedList &operator=(LinkedList &other); // TODO: to be implemented
    void pushFront(const T &);

    void pushBack(const T &);

    void popFront();

    void popBack();

    void dump();

private:
    class Node {
        friend class LinkedList<T>;

    private:
        T data;
        Node *link;

    public:
        Node(T d, Node *n = nullptr) : data(d), link(n) { }
    };

    Node *head;
    Node *tail;
    int len;
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &src) {
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


/**
 * returns lvalue reference to the head's data
 */
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
