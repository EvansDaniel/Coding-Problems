package evansdaniel.hackerrank;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by daniel on 8/23/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/contests/101hack40/challenges/next-topological-sorting
 */
public class NextTopologicalOrdering {

    static Hashtable<Integer, List<Integer>> incEdges;
    static Hashtable<Integer, List<Integer>> adjVerts;
    static List<Integer> p;

    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File
                (Config.getDataDir() + "NextTopologicalOrderingData"));

        int numVertices = s.nextInt();
        int numEdges = s.nextInt();

        // might need longs here
        incEdges = new Hashtable<>(numEdges);
        adjVerts = new Hashtable<>(numEdges);

        for (int i = 1; i < numVertices + 1; ++i) {
            incEdges.put(i, new ArrayList<>(numEdges));
            adjVerts.put(i, new ArrayList<>(numEdges));
        }

        for (int i = 0; i < numVertices; ++i) {
            int outVert = s.nextInt();
            int inVert = s.nextInt();
//            System.out.printf(" %d %d \n", outVert, inVert);
            // add inVertices b/c arrow comes from outVertice
            adjVerts.get(outVert).add(inVert);
            incEdges.get(inVert).add(outVert);
        }

        p = new ArrayList<>(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            p.add(s.nextInt());
        }

        // ------------- START ------------------------
        List<Integer> noDepVerts = findNoDepVerts(numVertices, incEdges);
        List<Integer> nextTop = new ArrayList<>(p.size());
        // iterate over values in p
        for (int i = 0; i < p.size(); ++i) {
            Integer minVert = Collections.min(noDepVerts);
            if (noDepVerts.size() > 1) {
                // add min vertice to next topological sort
                nextTop.add(minVert);
                // add all new no dependency verts to list
                noDepVerts.addAll(nt(noDepVerts, nextTop, minVert));
            } else {
                // add minVert to list remove from deps
                nextTop.add(minVert);
                noDepVerts.remove(minVert);
            }
        }
    }

    private static Collection<? extends Integer> nt
            (List<Integer> noDepVerts, List<Integer> nextTop, Integer minVert) {

        noDepVerts.remove(minVert);
        for (int i = 0; i < noDepVerts.size(); ++i) {
            noDepVerts.addAll(getNoDepVerts(minVert, nextTop));
        }
        return new ArrayList<>();
    }

    private static List<Integer> findNoDepVerts
            (int numVerts,
             Hashtable<Integer, List<Integer>> incEdges) {
        List<Integer> noDepVerts = new ArrayList<>();
        for (int i = 1; i < numVerts + 1; i++) {
            if (incEdges.get(i).size() == 0) {
//                System.out.println(i);
                noDepVerts.add(i);
            }
        }
        return noDepVerts;
    }

    public static Collection<? extends Integer> getNoDepVerts
            (Integer minVert, List<Integer> nextTop) {
        List<Integer> noDepVerts = new ArrayList<>();
        List<Integer> adjVert = adjVerts.get(minVert);
        for (int i = 0; i < adjVert.size(); i++) {
            boolean notDependent = false;
            for (Integer integer : incEdges.get(i)) {
                notDependent = nextTop.contains(integer);
            }
            if (notDependent)
                noDepVerts.add(i);
        }
        return noDepVerts;
    }
}
