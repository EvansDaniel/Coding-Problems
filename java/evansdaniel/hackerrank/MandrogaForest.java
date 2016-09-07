package evansdaniel.hackerrank;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by daniel on 9/6/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/contests/hourrank-12/challenges/fair-cut
 */
public class MandrogaForest {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File(Config.getDataDir() + "MandrogaForest"));

        int tests = s.nextInt();
        while (tests-- > 0) {
            int n = s.nextInt();
            int[] h = new int[n];
            for (int i = 0; i < h.length; ++i) {
                h[i] = s.nextInt();
            }
            Arrays.sort(h);
            int ans = 0;
            int p = 0;
            for (int i : h) {
                p += i;
            }
            for (int i = 0; i < n; ++i) {
                ans = Math.max(ans, p * (i + 1));
                p -= h[i];
            }
            System.out.println(ans);
        }
    }
}
