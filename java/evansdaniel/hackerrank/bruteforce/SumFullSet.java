package evansdaniel.hackerrank.bruteforce;

import java.util.HashMap;

/**
 * Created by daniel on 10/3/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://community.topcoder.com/stat?c=problem_statement&pm=14215
 */
public class SumFullSet {
    public static void main(String[] args) {
        int[] k = {16, 0, 43, 43, -36, -49, -46, -16, 40, 34, -43, -24, 13, -48, 45, 19, 12, 0, 43, 6, 26, -23, 50, 28, -3, 21, 46, 45, -32, -41, 0, -27, 42, 19, 47, -36, -21, -1, 5, -21, -28, -43, 23, -26, -5, 21, -41, 16, -37, 38};
        System.out.println(isSumFullSet(k));
    }

    public static String isSumFullSet(int[] k) {
        HashMap<Integer, Integer> t = new HashMap<>();
        for (int i = 0; i < k.length; i++) {
            t.put(i, k[i]);
        }
        for (int q = 0; q < k.length; q++) {
            for (int i = 0; i < k.length; i++) {
                if (q == i) continue;
                if (!t.containsValue(k[i] + k[q])) {
                    return "not closed";
                }
            }
        }
        return "closed";
    }
}
