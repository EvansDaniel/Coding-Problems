package evansdaniel.hackerrank.basic;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Created by daniel on 9/5/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://www.hackerrank.com/challenges/sparse-arrays
 */
public class SparseArrays {

    public static void main(String[] args) throws FileNotFoundException {

        Scanner s = new Scanner(new File(Config.getDataDir() + "SparseArrays"));
        int numStrings = s.nextInt();
        s.nextLine();
        Map<String, Integer> map = new HashMap<>(numStrings);
        for (int i = 0; i < numStrings; i++) {
            map = putInMap(s.nextLine(), map);
        }
        int queries = s.nextInt();
        s.nextLine();
        for (int i = 0; i < queries; i++) {
            String temp = s.nextLine();
            if (map.containsKey(temp))
                System.out.println(map.get(temp));
            else
                System.out.println(0);
        }
    }

    private static Map<String, Integer> putInMap(String s, Map<String, Integer> map) {
        if (map.containsKey(s))
            map.put(s, map.get(s) + 1);
        else
            map.put(s, 1);
        return map;
    }
}
