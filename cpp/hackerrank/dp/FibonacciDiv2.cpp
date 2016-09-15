// Author: Daniel Evans
// Question Prompt: https://community.topcoder.com/stat?c=problem_statement&pm=13159

#include <iostream>
#include <vector>

using namespace std;


int find(int n) {
    vector<int> dp((unsigned) n + 1);
    dp[0] = 0;
    dp[1] = 1;

    int i = 2;
    for (; i < 2 * n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
        if (dp[i] >= n) break; // real stopping condition
    }
    return min(n - dp[i - 1], dp[i] - n);
}

int main() {

    std::cout << find(12);
};