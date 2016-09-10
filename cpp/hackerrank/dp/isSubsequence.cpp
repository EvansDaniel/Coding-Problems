#include <string>
#include <iostream>


// Author: Daniel Evans
// Question Prompt: https://leetcode.com/problems/is-subsequence/

bool isSubsequence(std::string s, std::string t) {
    if (s.empty()) return false;
    for (int j = 0, i = 0; j < t.length(); ++j)
        if (t[j] == s[i] && ++i == s.length()) return true;
}

/*
int main() {
    std::string s = "abc";
    std::string t = "ahbgdc";

    std::cout << isSubsequence(s, t) << std::endl;
}*/
