package evansdaniel.hackerrank.dp;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

/**
 * Created by daniel on 9/4/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/challenges/array-splitting
 */
public class NikitaAndTheGame {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File(Config.getDataDir() + "NikitaAndTheGame"));

        int tests = s.nextInt();
        long[] a;
        while (tests-- > 0) {

            int aLen = s.nextInt();
            a = new long[aLen];
            for (int i = 0; i < a.length; i++) {
                a[i] = s.nextLong();
            }
            long sum = 0;
            boolean allZeroes = true;
            Set<Long> setSum = new HashSet<>(aLen);
            for (int i = 0; i < a.length; i++) {
                sum += a[i];
                setSum.add(sum);
                if (a[i] != 0) {
                    allZeroes = false;
                }
            }

            if (allZeroes) {
                System.out.println(a.length - 1);
            } else {
                System.out.println(findScore(setSum, 0, sum));
            }
        }
    }

    private static int findScore(Set<Long> setSum, long min, long max) {
        if (((min + max) % 2 == 0) && setSum.contains((min + max) / 2))
            return 1 + Math.max(findScore(setSum, min, (min + max) / 2),
                    findScore(setSum, (min + max) / 2, max));
        else
            return 0;
    }

}
