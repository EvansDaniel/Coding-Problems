

// Author: Daniel Evans
// Question Prompt: https://leetcode.com/problems/combination-sum-iv/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int combinationSum4(vector<int>& nums, int target) {
    vector<int> sortedNums(nums);
    sort(sortedNums.begin(), sortedNums.end());
    vector<int> results(target + 1, 0);
    results[0] = 1;
    for (int currTarget = 1; currTarget <= target; currTarget++) {
        for (int j =  0; j < sortedNums.size()
                         &&  sortedNums[j] <= currTarget; j++)
        {
            results[currTarget] += results[currTarget - sortedNums[j]];
        }
    }

    return results[target];
}

int main() {
    std::vector<int> v {1 , 2 , 3, 4 , 5 };
    std::cout << combinationSum4(v, 3);
};