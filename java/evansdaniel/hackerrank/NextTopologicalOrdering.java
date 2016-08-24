package evansdaniel.hackerrank;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by daniel on 8/23/16.
 *
 * @author Daniel Evans
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

    }

    private static List<Integer> findNoDepVerts
            (int numVerts, Hashtable<Integer, List<Integer>> incEdges) {
        List<Integer> noDepVerts = new ArrayList<>();
        for (int i = 1; i < numVerts + 1; i++) {
            if (NextTopologicalOrdering.incEdges.get(i).size() == 0) {
//                System.out.println(i);
                noDepVerts.add(i);
            }
        }
        return noDepVerts;
    }

}
