package evansdaniel.hackerrank.basic;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Created by daniel on 9/6/16.
 *
 * @author Daniel Evans
 * Question Prompt: https://www.hackerrank.com/contests/hourrank-12/challenges/repeated-string
 */
public class RepeatedString {

    static final char testChar = 'a';

    public static void main(String[] args) throws FileNotFoundException {
        Scanner scan = new Scanner(new File(Config.getDataDir() + "RepeatedStrings"));

        String s = scan.nextLine();
        long n = scan.nextLong();

        int numAInOne = getNumberOfA(s, Math.min(s.length(), n));
        if (n >= s.length()) {
            // number of repeated strings
            long repeatedStringNum = n / s.length() * numAInOne;

            for (int i = 0; i < (n % s.length()); i++) {
                if (s.charAt(i) == testChar) {
                    repeatedStringNum++;
                }
            }
            System.out.println(repeatedStringNum);

        } else {
            System.out.println(numAInOne);
        }
    }

    private static int getNumberOfA(String s, long min) {
        int as = 0;
        for (int i = 0; i < min; i++) {
            if (s.charAt(i) == testChar) {
                as++;
            }
        }
        return as;
    }
}
