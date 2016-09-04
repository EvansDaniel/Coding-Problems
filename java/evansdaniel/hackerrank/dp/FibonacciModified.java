package evansdaniel.hackerrank.dp;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigInteger;
import java.util.Scanner;

/**
 * Created by daniel on 9/3/16.
 *
 * @author Daniel Evans
 *         Question Promp: https://www.hackerrank.com/challenges/fibonacci-modified
 */
public class FibonacciModified {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner s = new Scanner(new File(Config.getDataDir() + "FibonacciModified"));

        BigInteger t1 = s.nextBigInteger();
        BigInteger t2 = s.nextBigInteger();
        int n = s.nextInt();
        BigInteger[] a = new BigInteger[n];
        a[0] = t1;
        a[1] = t2;

        for (int i = 2; i < n; i++) {
            BigInteger temp = a[i - 1].multiply(a[i - 1]);
            a[i] = a[i - 2].add(temp);
        }

        System.out.println(a[n - 1]);
    }
}
