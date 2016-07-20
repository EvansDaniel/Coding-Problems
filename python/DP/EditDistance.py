def edit_distance(str1, str2):
    m = len(str1)
    n = len(str2)
    # create an n x m matrix to store values
    dp = [[0] * (n + 1) for x in range(m + 1)]

    # iter thru str1
    for i in range(m + 1):
        # iter thru str2
        for j in range(n + 1):

            # If first string is empty, only option is to
            # insert all characters of second string
            if i == 0:
                dp[i][j] = j

            # If second string is empty, only option is to
            # remove all characters of second string
            elif j == 0:
                dp[i][j] = i

            # if last characters are the same, ignore the last character
            # and store the previous minimum operations in dp[i][j]
            elif str1[i - 1] == str2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]

            # the characters are different, find optimal solution to the subproblem
            # i.e. figure out if at this point it is optimal to either insert, remove, or replace
            # add 1 because we just performed one of the operations
            else:
                # do insert or replace or remove, whichever provides the min operations
                dp[i][j] = 1 + minimum([dp[i][j - 1],  # insert
                                        dp[i - 1][j - 1],  # replace
                                        dp[i - 1][j]])  # remove

    # returns the answer to the original problem
    return dp[m][n]


def minimum(array):
    min = array[0]
    for i in range(1, len(array)):
        min = array[i] if min > array[i] else min

    return min


str1 = "sunday"
str2 = "saturday"
print edit_distance(str1, str2)
