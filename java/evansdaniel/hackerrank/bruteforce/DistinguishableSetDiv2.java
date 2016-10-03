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
        // loops through the # of questions
        for (int i = 1; i < (1 << nq); i++) {

            HashSet<Integer> indexIntoString =
                    new HashSet<>();
            HashSet<String> pplAnswers = new HashSet<>();

            // generates the indexes into the strings
            // that make up a single subset
            for (int j = 0; j < nq; j++) {
                if ((i & (1 << j)) != 0) {
                    indexIntoString.add(j);
                    System.out.println("j = " + j);
                    for (int k = 0; k < np; k++)
                        d[k][j] = c[k][j];
                }
            }
            System.out.println("index into string = " + indexIntoString);
            StringBuilder sb;

            for (int p = 0; p < np; p++) {
                sb = new StringBuilder();
                for (int x : indexIntoString)
                    sb.append(d[p][x]);
                // duplicates won't be added, so if the some answers are
                // the same, the # of answers in pplAnswers won't be
                // equal to the number of
                pplAnswers.add(sb.toString());
            }
            System.out.println("Ppl answers = " + pplAnswers);
            System.out.println("size of pplAnswers = " + pplAnswers.size() + " ?=? " + np);
            if (pplAnswers.size() == np) {
                System.out.println("Incrementing # distinguishable sets, ds = " + ++ds);
            }
        }
        return ds;
    }
}
