package evansdaniel.hackerrank.greedy;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by daniel on 9/2/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/challenges/luck-balance
 */
public class LuckBalance {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File(Config.getDataDir() + "LuckBalance"));

        // K = contests that Lena can lose
        // N = number of preliminary contests
        int N, K;

        N = s.nextInt();
        K = s.nextInt();

        int[] L = new int[N];

        // Win the N - K smallest L[i] contests that are important
        // to achieve max luck balance
        int i = 0;
        int sum = 0;
        while (N-- > 0) {
            int l = s.nextInt();
            int important = s.nextInt();
            if (important == 1) { // important contest
                sum += L[i] = l; // sum the luck
                ++i;
            } else
                sum += l;
        }
        Arrays.sort(L);
        for (int j = 0; j < L.length - K; ++j) {
            if (L[j] == 0) continue; // skip zeroes b/c array could be oversized
            sum -= (2 * L[j]); // subtract luck twice b/c it has already been added once
        }
        System.out.println(sum);
    }
}
