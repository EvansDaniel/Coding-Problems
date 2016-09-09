
// Author: Daniel Evans
// Question Prompt: https://www.hackerrank.com/challenges/hr-city

#include <bits/stdc++.h>

using namespace std;
const long long P = 1000000007;

void solve() {
    int n;
    scanf("%d", &n);
    long long x =0,  // sum of distances from corner
            y=1,     // number of nodes
            z=0,     // diameter of tree, dist. from one corner to diametrical one
            ans=0;
    int a;
    for(int i =0; i<n; ++i){
        scanf("%d", &a);

        ans = ans*4 +
                (y*12+8)*x+
                (y*12+8)*y*a+
                (y*2+1)*(y*2+1)*a;

        x = x*4+
                (z+a*2)*y+
                (z+a*3)*y*2+
                (y*2+1)*(y*2+1)*a;

        z= z*2+a*3;

        ans%=P;

    }
    std::cout << ans << std::endl;
}