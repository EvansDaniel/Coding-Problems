package evansdaniel.hackerrank.greedy;

import evansdaniel.hackerrank.Config;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by daniel on 9/2/16.
 *
 * @author Daniel Evans - NEED TO REVIEW THIS
 *         Question Prompt: https://www.hackerrank.com/challenges/beautiful-pairs
 */
public class BeautifulPairs {

    public static void main(String[] args) throws FileNotFoundException {

        Scanner s = new Scanner(new File(Config.getDataDir() + "BeautifulPairs"));
        Map<Integer, Integer> ms = new HashMap<>();
        int n = s.nextInt();
        int[] a = new int[n];

        for (int i = 0; i < a.length; i++) {
            a[i] = s.nextInt();
        }
        for (int i = 0; i < n; i++) {
            int k = s.nextInt();
            ms = insertInto(ms, k);
        }

        int answer = 0;
        for (int i = 0; i < n; i++) {
            if (ms.get(a[i]) != null) {
                if (ms.get(a[i]) != 0) {
                    ms.put(a[i], ms.get(a[i]) - 1);
                    ++answer;
                }
            }
        }
        boolean isEmpty = true;
        Iterator<Map.Entry<Integer, Integer>> it = ms.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer, Integer> next = it.next();
            if (next.getValue() > 0) {
                isEmpty = false;
                break;
            }
        }
        System.out.println(isEmpty ? --answer : ++answer);
    }

    private static Map<Integer, Integer> insertInto
            (Map<Integer, Integer> ms, Integer k) {
        if (ms.get(k) == null)
            ms.put(k, 1);
        else
            ms.put(k, ms.get(k) + 1);
        return ms;
    }
}
