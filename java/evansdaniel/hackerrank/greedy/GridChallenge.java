package evansdaniel.hackerrank.greedy;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
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
        lines = s.nextInt();
        int[][] grid = new int[lines][lines];

        String nextLine = null;
        for (int i = 0; i < grid.length; i++) {
            nextLine = s.next();
            System.out.println(nextLine);
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
    }
}
