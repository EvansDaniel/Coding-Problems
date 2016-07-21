import sys


# returns the minimum operations to multiply the matrices
def chain_multiplication_matrix(matrices, i, j):
    if i == j:
        return 0

    myMin = sys.maxint
    count = 0

    k = i
    while k < j:
        count = chain_multiplication_matrix(matrices, i, k) + \
                chain_multiplication_matrix(matrices, k + 1, j) + \
                matrices[i - 1] * matrices[k] * matrices[j]
        if count < myMin:
            myMin = count
        k += 1

    return myMin


arr = [1, 2, 3, 4, 3]
n = 5
print chain_multiplication_matrix(arr, 1, n - 1)
