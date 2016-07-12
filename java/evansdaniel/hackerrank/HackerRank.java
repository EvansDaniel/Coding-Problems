package evansdaniel.hackerrank;

/**
 * Created by daniel on 7/12/16.
 */
public class HackerRank {

    /*
    Watson gives Sherlock an array  of length .
    Then he asks him to determine if there exists an element
    in the array such that the sum of the elements on its left
    is equal to the sum of the elements on its right.
    If there are no elements to the left/right, then the sum
    is considered to be zero. Formally, find an , such that,
    A[1]+A[2] .... A[i-1] = A[i+1] + A[i+2] ... A[N] (N = array.length)
    */
    // Solution:
    // Takes a string of numbers as input and returns
    // the index i where the sum of the elements to the left of
    // the i equal the sum of the elements to the right of i
    static int sameSum(String str) {
        int sum = 0;
        int left = 0;
        int right = 0;
        for (int i = 0; i < str.length() - 1; ++i) {
            int strNum = Character.getNumericValue(str.charAt(i));
            right = sum - left - strNum;
            if (left == right && (!(left == 0 && right == 0))) {
                System.out.println("YES");
                return i;
            }
            left += strNum;
        }
        System.out.println("NO");
        return -1;
    }

    static int maximizeSum(int[] array) {

        return -1;
    }
}
