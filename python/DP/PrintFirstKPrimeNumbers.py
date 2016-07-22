import math


def count_prime_factors(n):
    count = 0

    # count the number of 2s that divide n
    while n % 2 == 0:
        n /= 2
        count += 1

    # n is odd at this point
    # step by 2 because we can skip even numbers (n is odd)
    for i in range(3, int(math.sqrt(n)), 2):

        while n % i == 0:
            n /= i
            count += 1

    # n is either 1 or prime, thus if it is greater than 2, it must be prime
    # and there for we need to increment our count of prime factors
    if n > 2:
        count += 1

    return count


def print_first_n_kprime_numbers(n, k):
    count = 0
    num = 2
    while count < n:

        if count_prime_factors(num) == k:
            print num,
            count += 1
        num += 1


print_first_n_kprime_numbers(5, 2)
