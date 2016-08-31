package evansdaniel.hackerrank.geometry;

import evansdaniel.hackerrank.Config;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * Created by daniel on 8/23/16.
 *
 * @author Daniel Evans
 */

public class LasersMayor {

    // Question Prompt: https://www.hackerrank.com/contests/101hack40/challenges/lazy-mayor-and-lasers

    public static void main(String args[]) throws Exception {

        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(Config.getDataDir() + "lasersMayor.txt")));
        StringTokenizer st;

        int n = Integer.parseInt(in.readLine());
        st = new StringTokenizer(in.readLine());
        long[] h = new long[n];
        for (int i = 0; i < n; i++)
            h[i] = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(in.readLine());
        int[] x = new int[m];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < m; i++)
            x[i] = Integer.parseInt(st.nextToken()) - 1;
        Arrays.sort(x);

        // --------------
        int prev = 0;
        for (int t : x) {
            for (int i = t - 1; i >= prev; i--)
                h[i] = Math.min(h[i], t - i);
            prev = t;
        }
        long ans = 0;
        for (long i : h)
            ans += i;
        System.out.println(ans);
    }
}
