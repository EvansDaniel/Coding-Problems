// Author: Daniel Evans
// Problem Statement: https://community.topcoder.com/stat?c=problem_statement&pm=2402&rd=5009

#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int, int> answer;
vector<int> donations;

int maxDon(int i1, int i2) {

    int key = i1 * 500 + i2;
    if (answer.count(key)) return answer[key];
    if (i1 > i2) return 0;
    answer[key] = max(maxDon(i1 + 1, i2), maxDon(i1 + 2, i2) + donations[i1]);
    return answer[key];
}


int main() {
    donations = {1, 3, 65, 239, 49, 239, 209};
    int n = donations.size();
    std::cout << max(maxDon(0, n - 2), maxDon(1, n - 1));
};
