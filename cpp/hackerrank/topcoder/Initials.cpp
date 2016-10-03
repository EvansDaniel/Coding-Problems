// Author: Daniel Evans
// Question Prompt: https://community.topcoder.com/stat?c=problem_statement&pm=14389

#include <iostream>
#include <assert.h>

#define AT(str, i) (str.at((unsigned) i))

using namespace std;

string getInitals(string str) {

    string acro;
    // check if first char is space
    bool space = AT(str, 0) == ' ';
    // if first char is not a space, record it
    if (!space)
        acro += AT(str, 0);

    for (int i = 1; i < str.size(); ++i) {
        // if AT(str,i-1) == ' ', append ith char
        // b/c problem statement guarantees ith char != ' '
        if (space) {
            acro += AT(str, i);
            space = false;
        }
        // if ith iteration is a space
        if (AT(str, i) == ' ')
            space = true;
    }
    return acro;
}


int main() {

    string jfk = "a aa aaa aa a bbb bb b bb bbb";
    cout << getInitals(jfk);
    assert(getInitals(jfk) == "aaaaabbbbb");

}