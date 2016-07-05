//
// Created by daniel on 6/21/16.
//

#include <math.h>
#include <iostream>

bool isPerfectSquare(int num) {
    if (num == 1) return true;
    for (int divisor = 2; divisor <= num / divisor; ++divisor) {
        if (divisor * divisor == num)
            return true;
    }
    return false;
}

int main() {
    int n = 120;
    std::cout << isPerfectSquare(n);
};

