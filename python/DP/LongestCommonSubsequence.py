def longest_common_subsequence(str1, str2):
    #             columns                     rows
    dp = [[0] * (len(str2) + 1) for i in range(len(str1) + 1)]

    # r stands for rows, c stands for columns, str2 is along the columns, str1 is along the rows
    for r in range(len(str1) + 1):

        for c in range(len(str2) + 1):
            # value above dp[r][c] in dp 2d matrix
            top = dp[r - 1][c]
            # value left of dp[r][c] in dp 2d matrix
            left = dp[r][c - 1]
            # value diagonally across (top-left) from dp[r][c] in dp 2d matrix
            diag = dp[r - 1][c - 1]

            if r == 0 or c == 0:
                dp[r][c] = 0

            # use r-1 and c-1 because we are mapping the indices of the dp array onto the strings
            # and dp's length is 1 greater than the length of each string
            # when the characters of str1 and str2 are equal, take the diagonal's value + 1
            elif str1[r - 1] == str2[c - 1]:
                dp[r][c] = diag + 1

            # take the max of the value above or to the left in 2d array
            else:  # str1[r - 1] != str2[c - 1]
                dp[r][c] = max(top, left)

    # length of longest_common_subsequence is in dp[len(str1)[len(str2)]
    # the code that follows backtracks through dp to find the letters that 
    # make up the longest_common_subsequence
    valToPrint = [""] * (dp[len(str1)][len(str2)] + 1)
    index = len(valToPrint) - 1

    r = len(str1)
    c = len(str2)
    while r > 0 and c > 0:
        # value above dp[r][c] in dp 2d matrix
        top = dp[r - 1][c]
        # value left of dp[r][c] in dp 2d matrix
        left = dp[r][c - 1]

        if str1[r - 1] == str2[c - 1]:
            valToPrint[index - 1] = str1[r - 1]
            # go to the diagonal and update position of insertion for valToPrint
            r -= 1;
            c -= 1;
            index -= 1

        # go to the maximum of either the top or the left
        elif left > top:
            c -= 1
        else:
            r -= 1

    print "LCS of " + str1 + " and " + str2 + " is " + "".join(valToPrint)

    # return the length of longest_common_subsequence
    return dp[len(str1)][len(str2)]


str1 = "Pycharm"
str2 = "Python"

print longest_common_subsequence(str2.lower(), str1.lower())
