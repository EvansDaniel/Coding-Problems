package edu.evansdaniel.graphalgorithms;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * Created by daniel on 8/16/16.
 *
 * @author Daniel Evans
 */
public class Graph {

    private int graphEdges;
    private int graphVertices;
    private List<Integer>[] adjList;

    /**
     * Initializes an empty graph with <tt>graphVertices</tt> vertices and 0 edges.
     * param graphVertices the number of vertices
     *
     * @throws IllegalArgumentException if <tt>graphVertices</tt> < 0
     */
    @SuppressWarnings("unchecked")
    public Graph(int graphVertices) {
        if (graphVertices < 0) throw new IllegalArgumentException("Number of vertices must be nonnegative");
        this.graphVertices = graphVertices;
        this.graphEdges = 0;
        for (int v = 0; v < graphVertices; v++) {
            adjList[v] = new ArrayList<>();
        }
    }

    /**
     * Initializes a new graph that is a deep copy of <tt>G</tt>.
     *
     * @param G the graph to copy
     */
    @SuppressWarnings("unchecked")
    public Graph(Graph G) {
        this(G.graphVertices());
        this.graphEdges = G.graphEdges();
        // ali for AdjListIter
        for (int v = 0; v < G.graphVertices(); ++v) {
            Deque<Integer> stack = new ArrayDeque<>();
            for (int i = 0; i < G.adjList[i].size(); i++) {
                stack.push(G.adjList[i].get(i));
            }
            for (int i = 0; i < stack.size(); i++) {
                adjList[v].add(stack.pop());
            }
        }
    }

    public List<Integer> primMST(Graph graph) {
        
        return null;
    }


    /**
     * Returns the number of vertices in this graph.
     *
     * @return the number of vertices in this graph
     */
    public int graphVertices() {
        return graphVertices;
    }

    /**
     * Returns the number of edges in this graph.
     *
     * @return the number of edges in this graph
     */
    public int graphEdges() {
        return graphEdges;
    }

    // throw an IndexOutOfBoundsException unless 0 <= v < graphVertices
    private void validategraphVerticesertex(int v) {
        if (v < 0 || v >= graphVertices)
            throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (graphVertices - 1));
    }

    /**
     * Adds the undirected edge v-w to this graph.
     *
     * @param v one vertex in the edge
     * @param w the other vertex in the edge
     * @throws IndexOutOfBoundsException unless both 0 <= v < graphVertices and 0 <= w < graphVertices
     */
    public void addEdge(int v, int w) {
        validategraphVerticesertex(v);
        validategraphVerticesertex(w);
        graphEdges++;
        adjList[v].add(w);
        adjList[w].add(v);
    }


    /**
     * Returns the vertices adjListacent to vertex <tt>v</tt>.
     *
     * @param v the vertex
     * @return the vertices adjListacent to vertex <tt>v</tt>, as an iterable
     * @throws IndexOutOfBoundsException unless 0 <= v < graphVertices
     */
    public Iterable<Integer> adjList(int v) {
        validategraphVerticesertex(v);
        return adjList[v];
    }

    /**
     * Returns the degree of vertex <tt>v</tt>.
     *
     * @param v the vertex
     * @return the degree of vertex <tt>v</tt>
     * @throws IndexOutOfBoundsException unless 0 <= v < graphVertices
     */
    public int degree(int v) {
        validategraphVerticesertex(v);
        return adjList[v].size();
    }


    /**
     * Returns a string representation of this graph.
     *
     * @return the number of vertices <em>graphVertices</em>, followed by the number of edges <em>E</em>,
     * followed by the <em>graphVertices</em> adjListacency lists
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(graphVertices + " vertices, " + graphVertices + " edges " + "\n");
        for (int v = 0; v < graphVertices; v++) {
            s.append(v + ": ");
            for (int w : adjList[v]) {
                s.append(w + " ");
            }
            s.append("\n");
        }
        return s.toString();
    }
}
