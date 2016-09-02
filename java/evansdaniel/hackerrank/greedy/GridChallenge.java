package evansdaniel.hackerrank.greedy;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by daniel on 9/2/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/challenges/grid-challenge
 */
public class GridChallenge {
    public static void main(String[] args) throws FileNotFoundException {

        int tests, lines;
        Scanner s = new Scanner(new File(Config.getDataDir() + "GridChallenge"));
        tests = s.nextInt();
        while (tests-- > 0) {
            lines = s.nextInt();
            char[][] grid = new char[lines][lines];

            String nextLine = null;
            for (int i = 0; i < grid.length; i++) {
                nextLine = s.next();
                for (int j = 0; j < grid.length; j++) {
                    grid[i][j] = nextLine.charAt(j);
                }
            }
        /*for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid.length; j++) {
                System.out.printf("%c ", grid[i][j]);
            }
            System.out.println();
        }*/
            for (char[] chars : grid) {
                Arrays.sort(chars);
                System.out.println(Arrays.toString(chars));
            }
            boolean isSortedCorrectly = true;
            for (int i = 0; i < grid.length; i++) {
                for (int j = 1; j < grid.length; j++) {
                    System.out.print(grid[j][i] + " > " + grid[j - 1][i] + " ");
                    System.out.println();
                    if (!(grid[j][i] >= grid[j - 1][i])) {
                        isSortedCorrectly = false;
                        break;
                    }
                }
            }
            System.out.println(isSortedCorrectly ? "YES" : "NO");
        }
    }
}
