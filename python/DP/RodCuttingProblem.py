import sys


def cut_rod_problem_naive(p, size):
    if size == 0:
        return 0
    q = -sys.maxint
    for length in range(0, size):
        temp = p[length] + cut_rod_problem_naive(p, size - length - 1)
        if temp > q:
            q = temp

    return q


def top_down_cut_rod_problem(p, size):
    revenue = [-sys.maxint] * (size + 1)
    return td_cut_rod_problem_aux(p, size, revenue)


def bottom_up_cut_rod_problem(p):
    revenue = [0] * (len(p) + 1)
    # iterate through lengths
    for curr_length in range(1, len(p) + 1):
        max_revenue = 0
        # iterate through lengths < curr_length
        for sub_length in range(curr_length):
            max_revenue = max_value(max_revenue, p[sub_length] + revenue[curr_length - sub_length - 1])

        revenue[curr_length] = max_revenue
    return revenue[len(p)]


def max_value(a, b):
    return a if a > b else b


def td_cut_rod_problem_aux(p, size, revenue):
    # if we have the solution recorded
    if revenue[size] >= 0:
        return revenue[size]
    if size == 0:
        q = 0
    else:
        q = -sys.maxint
        for length in range(0, size):
            temp = p[length] + td_cut_rod_problem_aux(p, size - length - 1, revenue)
            if temp > q:
                q = temp
    revenue[size] = q
    return revenue[size]


print bottom_up_cut_rod_problem(
    [1, 5, 8, 9, 10, 17, 17, 20]
)
