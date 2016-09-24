// Author: Daniel Evans
// Question Prompt: https://community.topcoder.com/stat?c=problem_statement&pm=14389

#include <iostream>

using namespace std;

string getInitals(string str) {

    string acro = "";
    int a[str.size()];
    if (str.at(0) != ' ')
        acro += str.at(0);
    int temp = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str.at((unsigned) i) == ' ') {
            cout << i;
            a[temp] = i;
            temp++;
        }
    }
    acro += str.at(a[0] + 1);
    for (int i = 1; a[i] != 0; i++) {
        cout << i;
        if (a[i] + 1 < str.size())
            acro += str.at((unsigned) (a[i] + 1));
    }

    return acro;
}


int main() {

    string jfk = "john f.kennedy";
    cout << getInitals(jfk);

}