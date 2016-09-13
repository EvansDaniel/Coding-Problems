
// Author: Daniel Evans
// Question Prompt: https://leetcode.com/problems/guess-number-higher-or-lower-ii/

#include <climits>
#include <algorithm>
#include <iostream>

using namespace std;
//Cached recursion
int getMoneyAmountMemo(int s, int e,  vector<vector<int>> memo);
int getMoneyAmount(int s, int e,  vector<vector<int>> memo);

int getMoneyAmount(int n) {

    vector<vector<int>> memo(n+1, vector<int>(n+1, -1));

    //Call cached recursion
    return getMoneyAmountMemo(1, n, memo);
}
//Cached recursion
int getMoneyAmountMemo(int s, int e,  vector<vector<int>> memo) {
    //Check if the recursion is calculated before
    if (memo[s][e] == -1) {
        //Calculate recursion and save it to cache
        memo[s][e] = getMoneyAmount(s, e, memo);
    }
    return memo[s][e];
}

//Previous recursive solution. Added cache parameter to pass it to other recursion calls 
int getMoneyAmount(int s, int e,  vector<vector<int>> memo) {
    int diff = e - s;
    if (diff < 1) {
        return 0;
    }
    if (diff == 1) {
        return s;
    }
    if (diff == 2) {
        return s + 1;
    }
    int m = INT_MAX;
    for (int i = s + 1; i < e; i++) {
        //Now call for cached recursive function instead of directly calling basic recursive function
        m = min(i + max(getMoneyAmountMemo(s, i - 1, memo), getMoneyAmountMemo(i + 1, e, memo)), m);
    }
    return m;
}


int gmr(int s, int e);

int gmr(int s, int e) {
    int diff = e - s;
    //Base part
    if (diff < 1) {
        return 0;
    }
    if (diff == 1) {
        return s;
    }
    if (diff == 2) {
        return s + 1;
    }
    //Recursion part
    int min = INT_MAX;
    for (int i = s + 1; i < e; i++) {
        min = std::min(min, i + std::max(gmr(s  , i-1)
                ,gmr(i+1, e)));
    }
    return min;
}

int gmr(int n) {
    return gmr(1, n);
}

/*
int main() {

    cout << getMoneyAmount(10) << endl;
};
*/



