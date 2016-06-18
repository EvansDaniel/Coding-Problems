//
// Created by daniel on 6/18/16.
//

#ifndef CPPTEST_VECTOR_H
#define CPPTEST_VECTOR_H


// TODO: ADD ERROR CHECKING TO ALL METHODS
/**
 *                  QUESTIONS
 *  why does the move constructor use the member initializer
 *  list and the brackets???
 *  when to use std::move???
 */
/**
 * 1. Class will maintain a primitive array
 * via a pointer to te block of allocated memory
 *
 * 2. The class will implement the big five
 * to provide deep copy semantics for the copy
 * ctor and operator= and a destructor to reclaim the
 * array's memory
 *
 * 3. The Vector will provde a resize function to
 * change the size of the array and a reserve function
 * to chagne the capacity of the array
 *
 * 4. The class will provide an access and mutator version
 * of operator[]
 *
 * 5. The class will provide basic functions sucb as
 * size(), empty(), clear(), back(), pop_back(),
 * and push_back(). push_back() will call reserve if the
 * size == capacity
 *
 * 6.The class will provide support for the nested types
 * iterator and const_iterator and associated begin and end methods
 *
 */
#include <algorithm>
#include <iostream>

template<typename Object>
class Vector {
public:
    // what exactly does this explicit do?
    explicit Vector(int initSize = 0)
            : size{initSize}, capacity{INITIAL_CAPACITY + initSize},
              objects{new Object[capacity]} { }

    Vector(const Vector &rhs)
            : size{rhs.size}, capacity{rhs.capacity}, objects{new Object[capacity]} {
        objects = new Object[capacity];
        for (int i = 0; i < size; ++i) {
            objects[i] = rhs.objects[i];
        }
    }

    Vector &operator=(const Vector &rhs) {

        // need to double check that I don't need to swap
        // the members instead of the object
        Vector copy{rhs};
        std::swap(*this, copy);
        return *this;
    }

    ~Vector() {
        delete[] objects;
    }

    Vector(Vector &&rhs)
            : size{std::move(rhs.size)},
              capacity{std::move(rhs.capacity)},
              objects{std::move(rhs.objects)} {
        rhs.objects = nullptr;
        rhs.size = 0;
        rhs.capacity = 0;
    }

    Vector &operator=(Vector &&rhs) {
        std::swap(size, rhs.size);
        std::swap(capacity, rhs.capacity);
        std::swap(objects, rhs.objects);
        return *this;
    }

    Object &operator[](int index) {
        return objects[index];
    }

    const Object &operator[](int index) const {
        return objects[index];
    }

    bool empty() const {
        return size == 0;
    }

    /**
     * if newSize is less than, the size
     * member of the vector, this method does
     * nothing, otherwise it allocates a new array
     * with capacity == newSize
     */
    void resize(int newSize) {
        if (newSize < size)
            return;
        reserve(newSize);
    }

/**
 * capacity is the number of items that
 * can be stored in the internal array
 * without resizing
 */
    int getCapacity() const {
        return capacity;
    }

    /**
     * size is the number of items in the array
     * at this moment
     */
    int getSize() const {
        return size;
    }

    void push_back(const Object &d) {
        // resize internal array if there is no more space
        if (size == capacity)
            resize(size * 2 + 1);
        // add d to the array
        objects[size] = d;
        ++size;
    }

    void push_back(Object &&d) {
        if (size == capacity)
            resize(size * 2 + 1);
        objects[size] = std::move(d);
        ++size;
    }

    /** @pop_back()
     * no need to delete anything because the value
     * at size will be either overwritten later when
     * something else is added, or the memory will
     * be deallocated when the destructor is called
     */
    void pop_back() {
        --size;
    }

    void print() const {
        for (int i = 0; i < size; ++i)
            std::cout << objects[i] << std::endl;
    }

    // the first const makes this -> v.back() = d <- impossible
    // d is of type Object
    const Object &back() const {
        // to get the last item in Vector
        // we must go back one index because when we add
        // elements, we do: objects[size] = d; ++size;
        // meaning that size is always one after the last element
        return objects[size - 1];
    }

    // defines a pointer to object as iterator
    typedef Object *iterator;
    // defines a const pointer to object as iterator
    typedef Object *const_iterator;

    iterator begin() {
        return &objects[0];
    }

    const_iterator begin() const {
        return &objects[0];
    }

    iterator end() {
        return &objects[size];
    }

    const_iterator end() const {
        return &objects[size];
    }

private:
    // check this methods efficiency
    void reserve(int newSize) {
        capacity = newSize;
        // create new array of size newSize
        Object *temp = new Object[newSize];
        // copy current arrays contents
        for (int i = 0; i < this->size; ++i) {
            temp[i] = std::move(objects[i]);
        }
        // delete the memory pointed to by objects
        delete[] objects;
        // make objects point to the new array
        objects = temp;
    }

    static const int INITIAL_CAPACITY = 20;
    int size;
    int capacity;
    Object *objects;
};


#endif //CPPTEST_VECTOR_H
