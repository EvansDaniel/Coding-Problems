package evansdaniel.hackerrank;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Created by daniel on 8/31/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/contests/world-codesprint-6/challenges/bonetrousle
 */
public class BoneTrousle {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File(Config.getDataDir() + "BoneTrousle"));

        int trips = in.nextInt(); // 20
        while (trips-- > 0) {
            long n = in.nextLong(); // 10^18
            long k = in.nextLong(); // 10^18
            int b = in.nextInt();  // 10^5
            long minSum = 0;
            for (int i = 0; i < b; i++) {
                minSum += i + 1;
            }
            long maxSum = 0;
            for (int i = 0; i < b; i++) {
                maxSum += k - i;
                if (maxSum >= n) break;
            }
            if (n <= maxSum && n >= minSum) {
                int whichK = 0;
                for (int i = b; i > 0; --i) { // iter backwards thru barray
                    if (minSum - i + (k - whichK) >= n) {
                        System.out.printf("%d", n - minSum + i);
                        for (long j = 1; j < b - whichK; j++) System.out.printf(" %d", j);
                        for (long j = k - whichK; j < k; j++) System.out.printf(" %d", j + 1);
                        System.out.println();
                        break;
                    } else {
                        minSum -= i;
                        minSum += (k - whichK);
                        whichK++;
                    }
                }
            } else {
                System.out.println(-1);
            }
        }
    }
}
