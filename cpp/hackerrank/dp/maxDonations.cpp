// Author: Daniel Evans
// Problem Statement: https://community.topcoder.com/stat?c=problem_statement&pm=2402&rd=5009
#include <iostream>
#include <vector>
#include <map>


using namespace std;
map<int, int> dp;
vector<int> don;
map<int, int> p;

int maxDon(int i1, int end) {
    int key = i1 * 500 + end;
    if (dp.count(key)) return dp[key];
    if (i1 > end) return 0;
    dp[key] = max(maxDon(i1 + 1, end), don[i1] + maxDon(i1 + 2, end));
    return dp[key];
}
int main() {
    don = {10, 20, 30, 40, 50, 60};
    int n = don.size();
    cout << max(maxDon(0, n - 2), maxDon(1, n - 1));
};