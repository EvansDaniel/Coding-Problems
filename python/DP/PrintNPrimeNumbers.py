def print_first_n_prime_numbers(n):
    count = 0
    # i is the current number we are checking for "primeness"
    i = 2
    # iterate until we have printed n prime numbers
    while count < n:
        # p stands for prime, assume its true
        p = True
        # loop through 2 - 9 because if i is not divisible by any of these numbers then
        # i (is prime) will not be divisible by any numbers greater than 9 either
        for j in range(2, 9):
            # if j == i that means that i is prime
            if j == i:
                break
            # if i is divisible by j than it is not prime and stop loop
            if i % j == 0:
                p = False
                break

        # check if i was found to be prime
        if p:
            print i,
            # increment count since it keeps track of the number of prime numbers found
            count += 1
        # increment to the next number we check for "primeness"
        i += 1


print_first_n_prime_numbers(10)
