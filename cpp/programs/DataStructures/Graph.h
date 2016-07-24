//
// Created by daniel on 7/23/16.
//

#ifndef CPPTEST_GRAPH_H
#define CPPTEST_GRAPH_H

// A C Program to demonstrate adjacency list representation of graphs

#include <stdio.h>
#include <stdlib.h>

template<typename T>
class Graph {

private:
// A structure to represent an adjacency list node
    struct GraphNode {
        int dest;
        GraphNode *next;
    };

// A structure to represent an adjacency list
    struct AdjList {
        struct GraphNode *head;  // pointer to head node of list
    };

    int V;
    AdjList *array;

public:
// A utility function to create a new Graph node
    GraphNode *makeGraphNode(int dest) {
        GraphNode *newNode = new GraphNode;
        newNode->dest = dest;
        newNode->next = NULL;
        return newNode;
    }

// A utility function that creates a graph of V vertices
    Graph *createGraph(int V) {
        struct Graph *graph = new Graph;
        graph->V = V;

        // Create an array of adjacency lists.  Size of array will be V
        graph->array = new AdjList;

        // Initialize each adjacency list as empty by making head as NULL
        int i;
        for (i = 0; i < V; ++i)
            graph->array[i].head = NULL;

        return graph;
    }

// Adds an edge to an undirected graph
    void addEdge(int src, int dest) {
        // Add an edge from src to dest.  A new node is added to the adjacency
        // list of src.  The node is added at the begining
        GraphNode *newNode = makeGraphNode(dest);
        newNode->next = this->array[src].head;
        this->array[src].head = newNode;

        // Since graph is undirected, add an edge from dest to src also
        newNode = makeGraphNode(src);
        newNode->next = this->array[dest].head;
        this->array[dest].head = newNode;
    }

// A utility function to print the adjacenncy list representation of graph
    void printGraph() {
        int v;
        for (v = 0; v < this->V; ++v) {
            GraphNode *pCrawl = this->array[v].head;
            printf("\n Adjacency list of vertex %d\n head ", v);
            while (pCrawl) {
                printf("-> %d", pCrawl->dest);
                pCrawl = pCrawl->next;
            }
            printf("\n");
        }
    }

};

#endif //CPPTEST_GRAPH_H
