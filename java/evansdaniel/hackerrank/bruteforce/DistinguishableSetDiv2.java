package evansdaniel.hackerrank.bruteforce;

import java.util.HashSet;

/**
 * Created by daniel on 10/3/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://community.topcoder.com/stat?c=problem_solution&cr=40099699&rd=16774&pm=14305
 */
public class DistinguishableSetDiv2 {

    public static void main(String[] args) {
        String[] k = {"AA", "AB", "CC"};
        System.out.println(count(k));
    }


    public static int count(String[] ans) {
        int np = ans.length;
        int nq = ans[0].length();
        int ds = 0;
        char[][] c = new char[np][nq];
        for (int i = 0; i < np; i++) {
            c[i] = ans[i].toCharArray();
        }
        char[][] d = new char[np][nq];
        for (int i = 1; i < (1 << nq); i++) {

            HashSet<Integer> indexIntoString =
                    new HashSet<>();
            HashSet<String> pplAnswers = new HashSet<>();

            // generates the indexes into the strings
            // that make up a single subset
            for (int j = 0; j < nq; j++) {
                if ((i & (1 << j)) != 0) {
                    indexIntoString.add(j);
                    for (int k = 0; k < np; k++)
                        d[k][j] = c[k][j];
                }
            }
            StringBuilder sb;

            for (int p = 0; p < np; p++) {
                sb = new StringBuilder();
                for (int x : indexIntoString)
                    sb.append(d[p][x]);
                pplAnswers.add(sb.toString());
            }
            if (pplAnswers.size() == np)
                ds++;
        }
        return ds;
    }
}
