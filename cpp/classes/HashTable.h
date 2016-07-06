//
// Created by daniel on 7/4/16.
//

#ifndef CPPTEST_HASHTABLE_H
#define CPPTEST_HASHTABLE_H

#include <math.h>
#include <iostream>
#include "List.h"

using namespace std;

template<typename T>
class HashTable {

private:
    // hash table w/ chaining
    List<T> *data;
    int numElements;
    int capacity;
    const double A = 0.6180339887;
    double loadFactor = 0.75;


public:
    HashTable(int capacity = 100, double loadFactor = .75)
            : capacity{capacity}, numElements{0}, loadFactor{loadFactor} {
        this->data = new List<T>[capacity];
    }

    HashTable(const HashTable &rhs)
            : capacity{rhs.capacity}, numElements{rhs.numElements}, loadFactor{rhs.loadFactor} {
        this->data = new List<T>[rhs.capacity];
        List<T> *ptr = rhs.data;
        for (int i = 0; i < capacity; ++i) {
            typename List<T>::iterator itr = ptr->begin();
            // copy the stuff in each list
            while (itr != ptr->end()) {
                cout << "adding stuff from linked lists" << endl;
                this->data->push_back(*itr);
                ++itr;
            }
        }
        ptr = nullptr;
    }

    HashTable(HashTable &&rhs)
            : capacity{std::move(rhs.capacity)}, numElements{std::move(rhs.numElements)},
              loadFactor{std::move(rhs.loadFactor)} {
        rhs.capacity = 0;
        rhs.numElements = 0;
        rhs.loadFactor = 0;
        rhs.data = nullptr;
    }

    HashTable &operator=(const HashTable &rhs) {
        // make a copy of rhs
        HashTable copy = rhs;
        // swap the copy with *this; this is similar to the move copy assignment operator, but
        // instead of already having an object made for us (HashTable&& rhs), we have to make our own copy
        std::swap(*this, copy);
        return *this;
    }

    HashTable &operator=(HashTable &&rhs) {
        // swap the elements because we know that rhs will never be used again
        // which is because it will be destroyed soon
        std::swap(rhs.data, this->data);
        std::swap(rhs.capacity, this->capacity);
        std::swap(rhs.numElements, this->numElements);
        std::swap(rhs.loadFactor, this->loadFactor);
        return *this;
    }

    // multiplication method for hashing
    int hashFunction(T obj) {
        return floor(capacity * ((obj * A) % 1));
    }

    void insert(T obj) {
        data[hashFunction(obj)] = obj;
        ++numElements;
        if (capacity == (numElements * loadFactor)) {
            rehash();
        }
    }

    void search(T obj) { }

    void deleteObj(T obj) { }

    void rehash() {
        List<T> *temp = new List<T>[capacity * 2 + 1];

    }


    class const_iterator {
    public:
        const_iterator() : index{nullptr} { };

        const_iterator &operator++() {
            ++index;
            return *this;
        }

        const T &operator*() const {
            return retrieve();
        }

        const_iterator operator++(int) {
            const_iterator old = *this;
            ++index;
            return old;
        }

        const_iterator &operator--() {
            ++index;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator old = *this;
            ++index;
            return old;
        }


        bool operator==(const const_iterator &rhs) const {
            return index == rhs.index;
        }

        bool operator!=(const const_iterator &rhs) const {
            return index != rhs.index;
        }

    protected:
        T *index;

        const_iterator(T *i) : index{i} { };

        T &retrieve() const {
            return *index;
        }
    };

    class iterator : public const_iterator {
    public:
        iterator() { }

        T &operator*() {
            return const_iterator::retrieve();
        }

        const T &operator*() const {
            return const_iterator::operator*();
        }

        iterator &operator++() {
            this->index++;
            return *this;
        }

        iterator operator++(int) {
            auto old = *this;
            this->index++;
            return old;
        }

        iterator &operator--() {
            this->index--;
            return *this;
        }

        /**
         * this operator must return an rvalue
         * because its reference/temporary object is
         * destroyed at the end of this function
         *
         * IN GENERAL: It is impossible to return an lvalue
         * reference to a temporary object from a function for
         * the reason above
         */
        iterator operator--(int) {
            iterator old = *this;
            this->index--;
            return old;
        }

    protected:
        iterator(T *p) : const_iterator{p} { };

    };

};


#endif //CPPTEST_HASHTABLE_H
