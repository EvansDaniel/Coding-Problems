# function to return the transpose of a
# matrix representation of a graph; can
# also be used on any square matrix to
# get its transpose
def matrix_graph_transpose(matrix_graph):
    for r in range(0, len(matrix_graph)):
        # r to len(matrix_graph) because you can
        # only take transpose of a square matrix
        for c in range(r, len(matrix_graph)):
            temp = matrix_graph[r][c]
            matrix_graph[r][c] = matrix_graph[c][r]
            matrix_graph[c][r] = temp

    return matrix_graph


graph = [[0, 0, 0, 1], [1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0]]

print matrix_graph_transpose(graph)
