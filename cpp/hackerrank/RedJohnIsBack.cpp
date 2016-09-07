#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <cmath>
#include "../Config.h"

/*
 * Author: Daniel Evans
 * Question Prompt: https://www.hackerrank.com/challenges/red-john-is-back
 */

std::vector<int> sieve(int n)
{
    std::set<int> primes;
    std::vector<int> vec;

    primes.insert(2);

    for(int i=3; i<=n ; i+=2)
    {
        primes.insert(i);
    }

    int p=*primes.begin();
    vec.push_back(p);
    primes.erase(p);

    int maxRoot = sqrt(*(primes.rbegin()));

    while(primes.size() > 0)
    {
        if(p > maxRoot)
        {
            while(primes.size() > 0)
            {
                p=*primes.begin();
                vec.push_back(p);
                primes.erase(p);
            }
            break;
        }

        int i = p*p;
        int temp = (*(primes.rbegin()));

        while(i<=temp)
        {
            primes.erase(i);
            i += p;
            i += p;
        }

        p=*primes.begin();
        vec.push_back(p);
        primes.erase(p);
    }

    return vec;
}

int main() {

    int tests, N, i, count, result;
    std::ifstream redJohn;
    redJohn.open(Config::getDataDir() + "RedJohnIsBack");
    std:: vector<int> prime;
    std::vector<int>::iterator it;

    redJohn >> tests;
    prime = sieve(217286);
    int a[41];
    for(i=0; i<4; i++)
        a[i] = 1;
    for(i=4; i<41;++i)
        a[i] = a[i-1] + a[i-4];

    int numprime[41];
    for(i=0; i<41; ++i)
    {
        count = 0;
        for(it = prime.begin(); it != prime.end(); ++it) {
            if(*it <= a[i])
                ++count;
            else
                break;
        }
        numprime[i] = count; // keep track of num primes <= a[i]
    }
    while(tests--)
    {
        redJohn >> N;
        result = numprime[N];
        std::cout << result << std::endl;
    }
    return 0;
}