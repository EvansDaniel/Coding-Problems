// Author: Daniel Evans
// Question Prompt: https://community.topcoder.com/stat?c=problem_statement&pm=11341

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxTurns(vector<int> cards) {
    sort(cards.begin(), cards.end());
    int c = 0;
    for (int i = 0; i < cards.size();) {
        if (cards[i] == cards[i + 1] - 1)
            i += 2;
        else
            i++;
        c++;
    }
    return c;
}

/*
int main() {
    vector<int> v = {1, 4, 5, 7, 8, 9, 10};
    // expected output = 4
    cout << maxTurns(v);
}*/
