//
// Created by daniel on 7/4/16.
//

#ifndef CPPTEST_BITVECTOR_H
#define CPPTEST_BITVECTOR_H

#include <vector>
#include "List.h"

class BitVector {

private:

    BitVector(int capacity);

    bool *bitVector;
    int theSize;
    int capacity;

public:
    ~BitVector();

    BitVector(const BitVector &rhs);

    bool search(int index);

    void deleteBit(int index);

    void insert(int index);

    bool flipBit(int index);

    void ensureCapacity(int capacity);

    BitVector &operator=(const BitVector &rhs);

    BitVector &operator=(BitVector &&rhs);

    BitVector(BitVector &&rhs);

};


#endif //CPPTEST_BITVECTOR_H
