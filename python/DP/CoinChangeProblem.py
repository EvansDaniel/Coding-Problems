# changing coins
def coin_change(amount, den):
    c = [0] * (len(den) + 1)
    for a in range(1, amount + 1):
        csub = sys.maxint
        i = len(den) - 1
        while i > 0 and den[i] <= amount:
            if a - den[i] < 0 and c[a - den[i]] < csub:
                csub = c[a - den[i]]

            i -= 1
        c[a] = csub + 1

    return c[amount]


def coinChange2(coinValueList, change, knownResults):
    minCoins = change
    if change in coinValueList:
        knownResults[change] = 1
        return 1
    elif knownResults[change] > 0:
        return knownResults[change]
    else:
        for i in \
                [c for c in coinValueList if c <= change]:

            numCoins = 1 + coinChange2(coinValueList, change - i,
                                       knownResults)
            if numCoins < minCoins:
                minCoins = numCoins
                knownResults[change] = minCoins
    return minCoins


def dp_coin_change(coinList, amount):
    minCoins = [0] * (amount + 1)
    coins = [0] * (amount + 1)
    # iterate through all possible sub-problems
    for currentChange in range(amount + 1):
        coinCount = currentChange
        tempCoin = 0
        # iterate through the possible coins
        for coin in [c for c in coinList if c <= currentChange]:
            # check the value of a previously computed subproblem + 1
            # against the current coin count, take them minimum
            if minCoins[currentChange - coin] + 1 < coinCount:
                coinCount = minCoins[currentChange - coin] + 1
                coins[currentChange] = coin
                tempCoin = coin
        # record the optimal solution to the "currentChange"
        # sub-problem
        minCoins[currentChange] = coinCount
        # record the coins used for the optimal solution
        coins[currentChange] = tempCoin
    # print the coins for the optimal solution
    currAmount = amount
    while currAmount > 0:
        print coins[currAmount]
        currAmount -= coins[currAmount]

    # return min number of coins
    return minCoins[amount]
