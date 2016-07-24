//
// Created by daniel on 7/4/16.
//

#include "BitVector.h"

void BitVector::deleteBit(int index) {
    bitVector[index] = 0;
}

void BitVector::insert(int index) {
    bitVector[index] = 1;
}

bool BitVector::search(int index) {
    return bitVector[index];
}

bool BitVector::flipBit(int index) {
    return bitVector[index] = !bitVector[index];
}

void BitVector::ensureCapacity(int capacity) {
    if (capacity < this->theSize)
        capacity = this->capacity * 2 + 1;

    bool *temp = new bool[capacity];
    for (int i = 0; i < theSize; ++i) {
        temp[i] = bitVector[i];
    }
    delete[] bitVector;
    bitVector = temp;
}

// initializes the previous node, next node, head and tail nodes, and puts theSize == 0
BitVector::BitVector(int capacity) : bitVector{new bool[capacity]} { }

// removes and deallocates all the nodes in the list, including the sentinel nodes, head and tail
BitVector::~BitVector() {
    delete[] bitVector;
    bitVector = nullptr;
}

// copy constructor that uses the push back method to avoid low-level pointer manipulation
BitVector::BitVector(const BitVector &rhs) {
    bitVector = new bool[rhs.capacity];
    for (int i = 0; i < rhs.theSize; ++i) {
        bitVector[i] = rhs.bitVector[i];
    }
    theSize = rhs.theSize;
    capacity = rhs.capacity;
}

// passes list by reference, copies it, and swaps *this with the copy
BitVector &BitVector::operator=(const BitVector &rhs) {
    BitVector copy = rhs;
    std::swap(this->bitVector, rhs.bitVector);
    std::swap(this->capacity, rhs.capacity);
    std::swap(this->theSize, rhs.theSize);
    return *this;
}

// move constructor, initializes the node with the rvalue reference
// allowed to perform the move since rhs is about to be destroyed
BitVector::BitVector(BitVector &&rhs)
        : bitVector{rhs.bitVector} { }

// move assignment operator, we 'steal' rhs's member variables before it gets destroyed
// and return the new version of *this
BitVector &BitVector::operator=(BitVector &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);

    return *this;
}


