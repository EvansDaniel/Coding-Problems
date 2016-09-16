// Author: Daniel Evans
// Question Prompt: https://community.topcoder.com/stat?c=problem_statement&pm=10240

#include <iostream>

using namespace std;

int calculate(int k, int n) {

    int dp[k + 1][n + 1];

    for (int r = 0; r < k + 1; ++r) {
        for (int c = 0; c < n + 1; ++c) {
            dp[r][c] = 0;
        }
    }

    for (int c = 0; c < n + 1; ++c) {
        dp[0][c] = c + 1;
    }
    for (int r = 0; r < k + 1; ++r) {
        dp[r][0] = 1;
    }
    for (int r = 1; r < k + 1; ++r) {
        for (int c = 1; c < n + 1; ++c) {
            dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
        }
    }

    // prints the array
    /*for (int i = 0; i < k+1; ++i) {
        for (int j = 0; j < n+1; ++j)
            cout << dp[i][j] << " ";
        cout << endl;
    }*/

    return dp[k][n - 1];
}


/*int main() {
    cout << calculate(2, 3) << endl; // 10
    cout << calculate(4, 10) << endl; // 2002
    cout << calculate(10, 10) << endl; // 167960
};*/
