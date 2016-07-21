def numSolutionsToCoinChange_r(coins, numCoins, cents):
    if cents == 0:
        return 1
    if cents < 0:
        return 0
    if numCoins <= 0:
        return 0
    # 1st recursion finds solution that doesn't contain the last coin in coins (hence the numCoins - 1)
    # 2nd recursion finds solution that contains the last coin (coin at numCoins index) at least once
    return numSolutionsToCoinChange_r(coins, numCoins - 1, cents) + \
           numSolutionsToCoinChange_r(coins, numCoins, cents - coins[numCoins - 1])


print numSolutionsToCoinChange_r([1, 2, 3], 3, 5)


# assumes there is a coin with denomination 1
def numSolutionsToCoinChange(coins, cents):
    #           columns               rows
    dp = [[0] * (cents + 1) for i in range(len(coins))]

    # initialize the first column of dp to 1
    for r in range(len(coins)):
        dp[r][0] = 1
    # assumption from above is done here
    for c in range(1, cents + 1):
        if c % coins[0] == 0:
            dp[0][c] = 1
        else:
            dp[0][c] = 0

    for r in range(1, len(coins)):
        for c in range(1, cents + 1):
            if coins[r] > c:
                dp[r][c] = dp[r - 1][c]
            else:
                dp[r][c] = dp[r - 1][c] + dp[r][c - coins[r]]

    print dp

    return dp[len(coins) - 1][cents]


print numSolutionsToCoinChange([1, 2, 3], 5)
