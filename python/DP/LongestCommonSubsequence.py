def long_common_subsequence(str1, str2):
    #             columns                     rows
    dp = [[0] * (len(str2) + 1) for i in range(len(str1) + 1)]

    # r stands for rows, c stands for columns, str2 is along the columns, str1 is along the rows
    for r in range(len(str1) + 1):

        for c in range(len(str2) + 1):
            top = dp[r - 1][c]
            left = dp[r][c - 1]
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

    valToPrint = []
    r = len(str1)
    c = len(str2)
    while r >= 0 and c >= 0:
        if str1[r - 1] == str2[c - 1]:
            valToPrint.append(str1[r - 1])
            r -= 1
            c -= 1
            continue
        top = dp[r - 1][c]
        left = dp[r][c - 1]
        diag = dp[r - 1][c - 1]
        m = max(top, left, diag)
        # if they are all equal, go to the diagonal
        if top == diag and diag == left and top == left:
            r -= 1
            c -= 1
        # otherwise go to the max of the three
        elif m == top:
            r -= 1
        elif m == left:
            c -= 1
        elif m == diag:
            r -= 1
            c -= 1

    i = len(valToPrint) - 1
    while i >= 0:
        print valToPrint[i]
        i -= 1

    return dp[len(str1)][len(str2)]


str1 = "Pycharm"
str2 = "Python"

print long_common_subsequence(str2.lower(), str1.lower())
