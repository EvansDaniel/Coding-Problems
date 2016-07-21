# prints the diagonals of any matrix in a bottom-left to top-right manner
# think of it as following the L of the matrix, start at the top of the L
# and print diagonals bottom-left to top-right, ending at bottom-right of L
# r stands for rows and c stands for columns
def printDiags(matrix):
    for r in range(len(matrix)):
        r_temp = r
        c = 0
        while r_temp >= 0 and c < len(matrix[r]):
            print matrix[r_temp][c],
            # move up (r_temp-=1) and to the right (c+=1)
            r_temp -= 1
            c += 1
        # shows the particular diagonal clearly
        print ""
    r = len(matrix) - 1
    c = 1
    # iterate through remaining columns starting at the 1 column
    while c < len(matrix[r]):
        # need temporaries for c and r
        # because they will be changed in nested loop otherwise
        c_temp = c
        r_temp = r
        while c_temp < len(matrix[r]) and r_temp >= 0:
            print matrix[r_temp][c_temp],
            # move right (c_temp+=1) and left (r_temp-=1)
            c_temp += 1
            r_temp -= 1
        # shows the particular diagonal clearly
        print ""
        c += 1


matrix = [[1, 2, 3, 4],
          [5, 6, 7, 8],
          [1, 2, 3, 4],
          [5, 6, 7, 8]]

printDiags(matrix)
