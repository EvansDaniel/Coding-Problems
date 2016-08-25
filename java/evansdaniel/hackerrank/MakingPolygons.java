package evansdaniel.hackerrank;

/**
 * Created by daniel on 8/24/16.
 *
 * @author Daniel Evans
 * Question Prompt: https://www.hackerrank.com/contests/w22/challenges/polygon-making
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.IntStream;

public class MakingPolygons {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File(Config.getDataDir() + "MakingPolygons"));
        int n = in.nextInt();
        int a[] = new int[n];
        for (int a_i = 0; a_i < n; a_i++) {
            a[a_i] = in.nextInt();
        }
        if (n == 1)
            p(2); // make triangle
        else if (n == 2) {
            if (a[0] == (a[1]))
                p(2); // make square (all sides same length (cut at the middle for each) ) or rectangle
            else
                p(1); // cut larger
        } else {
            int sum = IntStream.of(a).sum();
            int twomax = 2 * Collections.max(Arrays.asList(IntStream.of(a).boxed().toArray(Integer[]::new)));
            if (sum <= twomax)
                p(1);  // sum of all sides <= max side, this would make degenerate polygon -> cut the max
            else
                p(0);  // sum of all sides > max side, we are able to make a non-degenerate polygon
        }
    }

    private static void p(int cuts) {
        System.out.println(cuts);
    }
}