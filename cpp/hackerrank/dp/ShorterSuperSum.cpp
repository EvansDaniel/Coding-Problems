// Author: Daniel Evans
// Question Prompt: https://community.topcoder.com/stat?c=problem_statement&pm=10240

#include <iostream>

using namespace std;

int calculate(int k, int n) {
    int dp[14][14];

    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 14; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n + 1; ++i) {
        dp[0][i] = 1;
    }
    for (int j = 0; j < n + 1; ++j) {
        dp[j][0] = j + 1;
    }

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < k + 1; ++j) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
        }
    }


/*
     for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 14; ++j)
            cout << dp[i][j] << " ";
        cout << endl;
    }*/
    return dp[n - 1][k];
}

int main() {
    cout << calculate(2, 3) << endl; // 10
    cout << calculate(4, 10) << endl; // 2002
    cout << calculate(10, 10) << endl; // 167960
};