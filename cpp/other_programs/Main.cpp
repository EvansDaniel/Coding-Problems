//
// Created by daniel on 6/21/16.
//

#include "../programs/DataStructures/Graph.h"

bool isPerfectSquare(int num) {
    if (num == 1) return true;
    for (int divisor = 2; divisor <= num / divisor; ++divisor) {
        if (divisor * divisor == num)
            return true;
    }
    return false;
}

int main() {
    Graph<int> graph;
    graph.addEdge(1, 2);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(5, 2);
    graph.addEdge(5, 1);
    graph.printGraph();
};
