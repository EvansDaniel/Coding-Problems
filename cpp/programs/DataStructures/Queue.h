//
// Created by daniel on 6/18/16.
//

#ifndef CPPTEST_QUEUE_H
#define CPPTEST_QUEUE_H

#include <algorithm>
#include <iostream>

/**
 * array implementation of a queue
 */
template<typename T>
class Queue {

public:
    T *line;
    int front;
    int index;
    int currentSize;
    int capacity;
    static const int INIT_CAPACITY = 3;

public:
    // ---------------------------------------------
    //             CONSTRUCTORS
    explicit Queue(int initSize = 0)
            : currentSize{0}, front{0},
              capacity{initSize + INIT_CAPACITY},
              index{0},
              line{new T[initSize + INIT_CAPACITY]} { }

    Queue(const Queue &rhs)
            : currentSize{rhs.currentSize},
              capacity{rhs.capacity}, front{rhs.front}, index{rhs.index},
              line{new T[rhs.currentSize]} {
        for (int i = 0; i < rhs.currentSize; ++i) {
            line[i] = rhs.line[i];
        }
    }

    Queue &operator=(Queue &&rhs) {
        std::swap(currentSize, rhs.currentSize);
        std::swap(front, rhs.front);
        std::swap(line, rhs.line);
        std::swap(index, rhs.index);
        std::swap(capacity, rhs.capacity);
        return *this;
    }

    Queue(Queue &&rhs)
            : currentSize{std::move(rhs.currentSize)},
              front{std::move(rhs.front)},
              index{std::move(rhs.index)},
              line{std::move(rhs.line)},
              capacity{std::move(rhs.capacity)} {
        rhs.line = nullptr;
        rhs.front = 0;
        rhs.index = 0;
        rhs.currentSize = 0;
        rhs.capacity = 0;
    }

    ~Queue() {
        delete[] this->line;
    }

    Queue &operator=(const Queue &rhs) {
        // this works
        Queue copy{rhs};
        std::swap(*this, copy);
        return *this;
    }

    // -------------------------------------------
    //               PUBLIC METHODS
    void enqueue(const T &d) {
        if (currentSize != capacity) {
            if (index == capacity) {
                index = 0;
            }
            line[index] = d;
        }
        else {
            // resize array
        }
        // increment position and size
        ++index;
        ++currentSize;
    }

    void enqueue(const T &&d) {
        if (currentSize != capacity) {
            if (index == capacity) {
                index = 0;
            }
        }
        else {
            resize(capacity * 2 + 1);
            // resizing must leave index at the first
            // position in the new array
        }
        // increment position and size
        line[index] = std::move(d);
        ++index;
        ++currentSize;
    }

    /**
     * deque() does nothing if the queue is empty
     */
    T deque() {
        T temp;
        if (!empty()) {
            // if we are at the end of the array
            if (front == capacity) {
                front = 0;
            }
            temp = line[front];
            ++front;
            --currentSize;
        }
        return temp;
    }

    bool empty() const {
        return currentSize == 0;
    }

    int getSize() const {
        return currentSize;
    }

    void resize(int newSize) {
        // maybe remove this check    ?????????
        if (newSize < currentSize)
            return;
        reserve(newSize);
    }

    void print() const {
        // there is only data ahead of front to print
        if (index > front) {
            for (int i = front; i < index; ++i)
                std::cout << line[i] << std::endl;
        } else {
            // print to the end of the array
            for (int i = front; i < capacity; ++i)
                std::cout << line[i] << std::endl;

            for (int i = 0; i < index; ++i)
                std::cout << line[i] << std::endl;
        }
    }

    T *copyArray(int capacity) {
        T *temp = new T[capacity];
        int j = 0;
        // copy from front to the end of the old array
        // old end == (capacity-1)/2
        for (int i = front; i < (capacity - 1) / 2; ++i, ++j)
            temp[j] = line[i];

        // if there is stuff behind front to copy
        if (index - 1 < front)
            for (int i = 0; i < index; ++i)
                temp[j] = line[i];
        // make front start at the beginning of the new array
        front = 0;
        // make index start at the end of the new array
        index = ((capacity - 1) / 2);
        return temp;
    }

    void reserve(int newSize) {
        capacity = newSize;
        // create new array of size newSize
        T *temp = copyArray(capacity);
        // delete the memory pointed to by objects
        delete[] line;
        // make objects point to the new array
        line = temp;
    }

};

#endif //CPPTEST_QUEUE_H
