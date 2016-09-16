// Author: Daniel Evans
// Question prompt: https://community.topcoder.com/stat?c=problem_statement&pm=10182


#include <iostream>

using namespace std;

int isPal(string str) {
    int s = 0, e = (int) str.size() - 1;
    while (s < e) {
        if (str[s++] != str[e--])
            return false;
    }
    return true;
}

int find(string s) {
    int i = 0;
    string add;
    while (i < s.size())
        if (isPal(s.substr(i++)))
            break;

    for (int j = 0; j + 1 < i; ++j)
        add += s[j];

    s += add;
    return (int) s.size();
}

int main() {
    string temp = "abdfhdyrbdbsdfghjkllkjhgfds";
    cout << find(temp) << endl; // 38
    temp = "qwerty";
    cout << find(temp) << endl; // 11
    temp = "abacaba";
    cout << find(temp) << endl; // 7

}