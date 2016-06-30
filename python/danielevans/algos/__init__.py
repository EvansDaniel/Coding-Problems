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
# remember that this median index represents the index of the
# median element IF THIS SEQUENCE IS SORTED. Note that the notion
# of a sequence below is assumed because most use cases will pass the length of
# an array i.e. sequence
def median_index(n):
    # if odd
    if n % 2:
        # take the middle element's index of the sequence
        return n // 2
    # even
    else:
        # take the lower index
        return (n // 2) - 1


# assumes m >= n
def median_index_of_range(n, m):
    # if odd
    if (m - n) % 2:
        # take the middle element's index of the sequence
        return (m - n) // 2
    # if even
    else:
        # take the lower index
        return ((m - n) // 2) - 1


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


def compute_lower_bounds(pivot, k):
    # if k is odd it will cause and large enough,
    # it will cause bound to be negative
    bound = pivot - (k // 2) - (k % 2)
    if bound < 0:
        # since bound is negative, we will take this into account for the
        # the upper bound computation and adjust upper bound accordingly
        # to produce kth elements
        return pivot - (k // 2)

    return bound


def compute_upper_bounds(pivot, k):
    # builds the knowledge of what happened in the lower bound computation
    bound = pivot - (k // 2) - (k % 2)
    if bound < 0:
        # add the k % 2 that was added in the lower bound to the upper bound
        return pivot + (k // 2) + 1 + (k % 2)
    else:
        # this means that lower bound took the extra k % 2
        # so we don't need to add that here
        return pivot + (k // 2) + 1


# will list the numbers that come median-k/2 before the median
# and the #s that come median+k/2 + 1 after the median
# happens a little differently if k is odd; we try to add an
# extra number to the lower portion (median-k/2-(k%2)) and if we go out of bounds
# we add an extra number to the upper range (median+k/2+(k%2))
def find_kth_nums_by_median(a, k):
    m = median_index(len(a))

    r = []
    for i in range(compute_lower_bounds(m, k), m):
        r.append(select(a, i))

    for i in range(m + 1, compute_upper_bounds(m, k)):
        r.append(select(a, i))

    return r


# does the same thing as find_kth_nums_by_median, just a different approach
# using the distance of the numbers from the median index
# unfortunately this function has a bug when k = 2 and a = [1,2,3,4,5,6]
# TODO: FIX THE BUG
def kth_distance_away(a, k):
    med_i = median_index(len(a))
    # r records the distances between the other elements and the med_i
    r = []
    for i in range(0, len(a)):
        if i != med_i:
            temp = med_i - i
            # if i > med_i, temp will be negative
            if temp < 0:
                # flip temp
                temp = -temp
            # add that distance to r
            r.append(temp)

    # find the rank k - 1 element value
    kth = select(a, k - 1)
    # stores output elements
    h = []
    for i in range(med_i - kth / 2, len(r)):
        if i != med_i:
            # if distance is less than the kth element
            if r[i] <= kth:
                h.append(a[i])
    return h


# assumes a and b are sorted arrays
# and that and b have the same number of elements
def two_array_median(a, b):
    # a = [1, 2, 3, 7]
    med = median_index(len(a))
    if a[med] == b[med] or len(a) == 1:
        return a[med] if a[med] < b[med] else b[med]

    if a[med] > b[med]:
        if a[med] <= b[med + 1]:
            print a[med]
            return a[med]
        else:
            two_array_median(a[0:med + 1], b[med + 1:])
    else:
        if b[med] <= a[med + 1]:
            # print b[med]
            return b[med]
        else:
            two_array_median(a[med + 1:], b[0:med + 1])


# end functions --------------------------------------------
# 1,2,3,4,[5],6,7,8,9,10
def main():
    a = [1, 4, 8, 9]
    b = [2, 5, 9, 10]

    print two_array_median(a, b)


main()
