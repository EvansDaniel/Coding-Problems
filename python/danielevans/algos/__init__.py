import math


def selectNth(a, n):
    med = median(a)
    smaller = [item for item in a if item < med]
    larger = [item for item in a if item > med]

    if len(smaller) == n:
        return med
    elif len(smaller) > n:
        return select(smaller, n)
    else:
        return select(list(larger), n - len(smaller) - 1)


def median(a):
    def median_index(n):
        if n % 2:
            return n // 2
        else:
            return n // 2 - 1

    def partition(a, element):
        i = 0

        for j in range(len(a) - 1):
            if a[j] == element:
                a[j], a[-1] = a[-1], a[j]

            if a[j] < element:
                a[i], a[j] = a[j], a[i]
                i += 1

        a[i], a[-1] = a[-1], a[i]

        return i

    def select(a, n):

        if len(a) <= 1:
            return a[0]

        medians = []

        for i in range(0, len(a), 5):
            group = sorted(a[i:i + 5])
            a[i:i + 5] = group
            median = group[median_index(len(group))]
            medians.append(median)

            pivot = select(medians, median_index(len(medians)))
            index = partition(a, pivot)

            if n == index:
                return a[index]
            elif n < index:
                return select(a[:index], n)
            else:
                return select(a[:], median_index(len(a)))

    return select(a[:], median_index(len(a)))


def k_quantiles(a, k):
    # return empty list if k == 1
    if k == 1:
        return []
    # if k is odd
    elif k % 2:
        n = len(a)
        # left median index
        left_index = math.ceil((k // 2) * (n / k)) - 1
        # right median index
        right_index = n - left_index - 1

        # value at left median index
        left = select(a, left_index)
        # value at right median index
        right = select(a, right_index)

        partition(a, left)
        # find the k_quantiles of the lower partition, [0,left)
        lower = k_quantiles(a[:left], k // 2)
        partition(a, right)
        # find the kth quantiles of the right partition, [right=left+1, len(a))
        upper = k_quantiles(a[right + 1:], k // 2)

        return lower + [left, right] + upper
    # if k is even
    else:
        index = median_index(len(a))
        median = select(a, index)
        partition(a, median)

        return k_quantiles(a[:index], k // 2) + \
               [median] + \
               k_quantiles(a[index + 1:], k // 2)


# returns the lower median index in some range [0,n]
def median_index(n):
    if n % 2:
        return n // 2
    else:
        return (n // 2) - 1


def partition(a, element):
    i = 0
    # put elements less than element to the left of element
    # put elements > element to the right of element
    for j in range(len(a) - 1):
        if a[j] == element:
            a[j], a[-1] = a[-1], a[j]

        if a[j] < element:
            a[i], a[j] = a[j], a[i]
            i += 1
    # swap the last known element < element with the end element
    a[i], a[-1] = a[-1], a[i]

    return i


# bug if a < k and len(a) > 1
def select(a, n):
    # if 1 element
    if len(a) == 1:
        return a[0]
    elif len(a) <= 0:
        raise IndexError("len(a) cannot be <= 0")

    # declare medians array
    medians = []
    # insertion sort each every 5 elements, store them in group, assign them
    # back to a[i:i+5], append the median found in group to the medians array
    for i in range(0, len(a), 5):
        group = sorted(a[i:i + 5])
        a[i:i + 5] = group
        median = group[median_index(len(group))]
        medians.append(median)
    # find the median of medians in the medians array
    # by calling select recursively
    pivot = select(medians, median_index(len(medians)))
    # partition the passed array around the median of medians (pivot)
    index = partition(a, pivot)
    # if the n == the ith element found (represented by index)
    if n == index:
        return a[index]
    elif n < index:
        # if less than, look in the left partition
        return select(a[:index], n)
    else:
        # if greater than, look in the right partition
        return select(a[index + 1:], n - index - 1)


# end functions --------------------------------------------
a = [1, 2, 3, 4]
k = 2

print select(a, k)
