

// Author: Daniel Evans
// Question Prompt: https://leetcode.com/problems/wiggle-subsequence/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// O(n^2) solution w/ dynamic programming
int wiggleMaxLength(vector<int> nums) {
    if (nums.size() < 2)
        return nums.size();
    vector<int> up(nums.size(),0);
    vector<int> down(nums.size(),0);
    for (int i = 1; i < nums.size(); i++)
        for(int j = 0; j < i; j++) {
            if (nums[i] > nums[j])
                up[i] = max(up[i], down[j] + 1);
            else if (nums[i] < nums[j])
                down[i] = max(down[i], up[j] + 1);
        }
    return 1 + max(down[nums.size() - 1], up[nums.size() - 1]);
}
// O(n) solution w/ dynamic programming
// could be optimized further by turning up and down into int vars
// and using them to keep track of the max wiggle subsequence after
// considering the ith element
int wiggleMaxLen(vector<int>& nums) {

    if(nums.size() < 2)
        return nums.size();

    vector<int> up(nums.size(),0);
    vector<int> down(nums.size(), 0);

    up[0] = down[0] = 1;
    for (int i = 1; i < nums.size(); ++i) {
        if(nums[i] > nums[i-1]) {
            up[i] = down[i-1] + 1;
            down[i] = down[i-1];
        }
        else if(nums[i] < nums[i-1]) {
            down[i] = up[i-1] + 1;
            up[i] = up[i-1];
        }
        else {
            down[i] = down[i-1];
            up[i] = up[i-1];
        }
    }
    // return the biggest wiggle sequence of the whole aray
    return max(down[nums.size() - 1], up[nums.size() - 1]);
}

int main() {
    std::vector<int> v {1,7,4,9,2,5};
    std::cout << wiggleMaxLen(v);
};