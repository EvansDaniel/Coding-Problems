import sys


def longest_common_substring(s1, s2):
    dp = [[0] * (len(s2) + 1) for i in range(len(s1) + 1)]

    myMax = -sys.maxint
    for r in range(1, len(s1) + 1):
        for c in range(1, len(s2) + 1):
            if s1[r - 1] == s2[c - 1]:
                dp[r][c] = dp[r - 1][c - 1] + 1
                myMax = dp[r][c] if myMax < dp[r][c] else myMax
            else:
                dp[r][c] = 0
    return myMax


s1 = "ABCDAF"
s2 = "ZBCDF"

print longest_common_substring(s1, s2)
