//
// Created by daniel on 6/21/16.
//

#include "../programs/DataStructures/BinarySearchTree.h"
#include "../programs/DataStructures/BinarySearchTree.h"
#include "../programs/DP/LongIncSub.h"
#include <typeinfo>
#include <zconf.h>

bool isPerfectSquare(int num) {
    if (num == 1) return true;
    for (int divisor = 2; divisor <= num / divisor; ++divisor) {
        if (divisor * divisor == num)
            return true;
    }
    return false;
}

int main() {
    int x[] = {1,2,3,4,5,6,7,8,9};
    std::cout << longIncSub(x, 9);
};
