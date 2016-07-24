//
// Created by daniel on 7/20/16.
//

#ifndef CPPTEST_LONGINCSUB_H
#define CPPTEST_LONGINCSUB_H

//
// Created by daniel on 7/20/16.
//

/* lis() returns the length of the longest increasing
  subsequence in arr[] of size n */
int longIncSub(int seq[], int n) {
    int i, j, max = 0;
    int lis[n + 1];
    int s[n + 1];

    /* Initialize LIS values for all indexes */
    for (i = 0; i < n; i++)
        lis[i] = 1;

    /* Compute optimized LIS values in bottom up manner */
    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (seq[i] > seq[j] && lis[i] < lis[j] + 1) {
                s[j] = seq[i];
                lis[i] = lis[j] + 1;
            }

    int k = 0;
    while(k < n+1) {

        ++k;
    }


    /* Pick maximum of all LIS values */
    for (i = 0; i < n; i++)
        if (max < lis[i])
            max = lis[i];

    return max;
}

#endif //CPPTEST_LONGINCSUB_H
