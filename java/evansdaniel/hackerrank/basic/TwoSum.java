package evansdaniel.hackerrank.basic;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by daniel on 9/4/16.
 *
 * @author Daniel Evans
 *         Question Prompt: https://leetcode.com/problems/two-sum/
 */
public class TwoSum {

    public static void main(String[] args) throws FileNotFoundException {
        // public int[] twoSum(int[] nums, int target) {
        Scanner s = new Scanner(new File(Config.getDataDir() + "TwoSum"));
        int target = s.nextInt();
        int len = s.nextInt();
        int[] a = new int[len];
        for (int i = 0; i < len; i++) {
            a[i] = s.nextInt();
        }
        System.out.println(Arrays.toString(twoSum(a, target)));
    }

    public static int[] twoSum(int[] a, int target) {
        Map<Integer, Integer> map = new HashMap<>(a.length);
        for (int i = 0; i < a.length; i++) {
            map.put(a[i], i);
        }
        for (int i = 0; i < a.length; i++) {
            int complement = target - a[i];
            if (map.containsKey(complement) && map.get(complement) != i) {
                return new int[]{i, map.get(complement)};
            }
        }
        throw new NoSuchElementException("No two elements found such that their sum equals target");
    }
}
