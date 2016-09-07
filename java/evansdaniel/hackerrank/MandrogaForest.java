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
            long ans = 0, p = 0;
            for (int i : h) {
                p += i;
            }
            // strength increased every iteration to simulate
            // eating the monster instead of battling it
            for (int strength = 0; strength < n; ++strength) {
                // answer keeps track of the max experience points of each n+1 possibilities
                ans = Math.max(ans, p * (strength + 1));
                // subtract the health b/c on next iteration we will
                // assume we ate the monster not battled it
                p -= h[strength];
            }
            System.out.println(ans);
        }
    }
}
