def fib_seq(n):
    pp = 0
    p = 0
    for i in range(1, n + 1):
        if i <= 2:
            f = 1
        else:
            f = p + pp
        p = f
        pp = p
    return p
