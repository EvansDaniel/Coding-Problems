"""
Binomial Coefficients:

The binomial coefficient are of the form
(n, k) or "n choose k" which take the values n!/(k!(n-k)!)

binomial coefficients form Pascal's Triangle

    1     n == 0
   1 1    n == 1
  1 2 1   n == 2
 1 3 3 1  n == 3
1 4 6 4 1 n == 4

This suggests a recursive definition of the binomial coefficient:
bc(n, k) = bc(n-1, k-1) + bc(n, k-1)
with base cases:
bc(n, 0) = 1
bc(n, n) = 1

"""


def bc(n, k):
    if k == 0 or k == n:
        return 1

    return bc(n - 1, k - 1) + \
           bc(n - 1, k)


def factorial(n):
    if n == 1:
        return 1
    return n * factorial(n - 1)


# another way to calculate BC w/ n!/(k!(n-k)!) formula (uses factorial recursive function above)
def binCoeff(n, k):
    return factorial(n) / (factorial(k) * factorial(n - k))


# binomial coefficient using dynamic programming
# bottom-up fashion which will basically build the Pascal Triangle
def bc_dp(n, k):
    dp = [[0] * (k + 1) for i in range(n + 1)]

    for r in range(n + 1):
        for c in range(k + 1):
            if c == 0 or c == n:
                dp[r][c] = 1
            else:
                dp[r][c] = dp[r - 1][c - 1] + dp[r - 1][c]

    return dp[n][k]


n = 5
k = 6

print bc_dp(n, k)
