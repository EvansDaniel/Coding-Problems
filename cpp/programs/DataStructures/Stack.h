//
// Created by daniel on 6/17/16.
//

#ifndef CPPTEST_STACK_H
#define CPPTEST_STACK_H

#include "SinglyLinkedList.h"

/**
 *      Recursive function calls requires saving the
 *      variable data in each call. Writing this information
 *      to the stack and popping it from the stack makes it  a
 *      little less efficient than iteration, not to mention the
 *      fact that recursive calls take up a lot of memory on the
 *      stack
 *
 *      Tail recursion refers to a recursive call in the last line of
 *      a function. It can be replaced by a loop with one assignment per
 *      function argument.
 */
template<typename T>
class Stack {

private:
    SSL<T> list;

public:
    Stack();

    ~Stack();

    Stack(const Stack &s);

    Stack &operator=(Stack rhs);

    Stack &operator=(Stack &&rhs);

    Stack(Stack &&rhs);

    const T pop();

    const T push(const T &d);

    bool empty() const;

    const T peek() const;

};

template<typename T>
Stack<T>::Stack() : list() { };

template<typename T>
Stack<T>::~Stack() {
    list.clear();
}

template<typename T>
Stack<T>::Stack(const Stack<T> &s) {
    // depends on list's operator=
    // implementation, (copy and swap)
    this->list = s.list;
}

template<typename T>
Stack<T> &Stack<T>::operator=(Stack<T> rhs) {
    std::swap(list, rhs.list);
    // deference operator returns an lvalue reference
    return *this;
}

template<typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&rhs) {

}

template<typename T>
Stack<T>::Stack(Stack<T> &&rhs)
        : list{std::move(rhs.list)} { }

/**
 * removes the element at the top of the stack
 * and returns the data it contained
 */
template<typename T>
const T Stack<T>::pop() {
    T d = *list.begin();
    list.pop_front();
    return d;
}

/**
 * returns the data on the top of the stack
 * if the stack is empty, it does nothing
 */
template<typename T>
const T Stack<T>::peek() const {
    if (!this->empty())
        return *(list.begin());
}

/**
 * adds T to the top of the stack
 */
template<typename T>
const T Stack<T>::push(const T &d) {
    list.push_front(d);
}

/**
 * returns true if there is nothing in the stack
 */
template<typename T>
bool Stack<T>::empty() const {
    return list.empty();
}





#endif //CPPTEST_STACK_H
