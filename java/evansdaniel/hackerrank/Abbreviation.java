package evansdaniel.hackerrank;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Created by daniel on 8/31/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/contests/world-codesprint-6/challenges/abbr
 */
public class Abbreviation {

    static boolean[][] dp = new boolean[1011][1011];

    public static void main(String[] args) throws FileNotFoundException {

        Scanner s = new Scanner(new File(Config.getDataDir() + "Abbreviation"));
        int test = s.nextInt();
        s.nextLine();
        while (test-- > 0) {
            String s1 = s.nextLine();
            String s2 = s.nextLine();

            for (int i = 0; i <= s1.length(); i++) {
                for (int j = 0; j <= s2.length(); j++) {
                    dp[i][j] = false;
                }
            }

            dp[0][0] = true;
            Character c = null;
            for (int i = 0; i < s1.length(); i++) {
                for (int j = 0; j <= s2.length(); j++) {
                    c = s1.charAt(i);
                    if (dp[i][j]) {
                        if (j < s2.length() && Character.toUpperCase(c) == s2.charAt(j))
                            dp[i + 1][j + 1] = true;
                        if (Character.isLowerCase(c))
                            dp[i + 1][j] = true;
                    }
                }
            }
            System.out.println(dp[s1.length()][s2.length()] ? "YES" : "NO");
        }
    }
}
