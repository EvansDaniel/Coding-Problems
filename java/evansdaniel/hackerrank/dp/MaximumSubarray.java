package evansdaniel.hackerrank.dp;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Created by daniel on 9/3/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/challenges/maxsubarray
 */
public class MaximumSubarray {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File(Config.getDataDir() + "MaximumSubarray"));

        int tests = s.nextInt();
        int n;
        int[] a;
        while (tests-- > 0) {
            n = s.nextInt();
            a = new int[n];
            for (int i = 0; i < a.length; i++)
                a[i] = s.nextInt();

            int bestSum = a[0];
            int currSum = a[0];
            for (int i = 1; i < a.length; i++) {
                currSum = Math.max(currSum + a[i], a[i]);
                bestSum = Math.max(bestSum, currSum);
            }
            System.out.print(bestSum + " ");
            bestSum = Integer.MIN_VALUE;
            currSum = 0;
            for (int i = 0; i < a.length; i++) {
                if (a[i] > bestSum)
                    bestSum = a[i];
                if (a[i] > 0)
                    currSum += a[i];
            }
            System.out.print((currSum > bestSum && currSum != 0) ? currSum : bestSum);
            System.out.println();
        }
    }
}
