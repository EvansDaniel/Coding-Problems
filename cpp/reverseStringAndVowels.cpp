#include <string>
#include <iostream>

void swap(std::string &x, int firstIdx, int secIdx);
std::string reverseString(std::string s);
std::string reverseVowels(std::string str);
bool isVowel(char ch);

// cause who wants to type more when you don't have to
using namespace std;

int main ()
{
    std::string s = "race car";
    std::string hello = "hello world";
    string want = "This is a test";
    cout << "Normal words:" << endl << s << endl << hello << endl << want << endl << endl;
    cout << "Reversed words:" << endl << reverseString(s) << endl << reverseString(hello) << endl << reverseString(want) << endl << endl;

    cout << "Normal vowels:" << endl << s << endl << hello << endl << want << endl << endl;
    cout << "Reversed Vowels:" << endl << reverseVowels(s) << endl << reverseVowels(hello) << endl << reverseVowels(want) << endl;

    return 0;
}
std::string reverseString(std::string s) {

    for(int i=0; i < s.length()/2; ++i) {
        swap(s,i,s.length()-i-1);
    }
    return s;
}
std::string reverseVowels(std::string s) {

    for (int i = 0, j = s.size() - 1; i < j;)
    {
        if (!isVowel(s[i]))
        {
            ++i;
        }
        else if (!isVowel(s[j]))
        {
            --j;
        }
        else
        {
            swap(s, i++, j--);
        }
    }
    return s;
}

bool isVowel(char ch) {
    ch = toupper(ch);
    return (ch=='A') || (ch=='E') || (ch=='I') || (ch=='O') ||(ch=='U');
}

void swap(std::string &x, int firstIdx, int secIdx) {

    // if either index is out of bounds -> = length of string
    if(firstIdx == x.length() || secIdx == x.length()) {
        std::cout << "Index passed == len of string -> "
        + std::to_string(x.length());

        return;
    }
    char temp = x.at(secIdx);
    x.at(secIdx) = x.at(firstIdx);
    x.at(firstIdx) = temp;
}

