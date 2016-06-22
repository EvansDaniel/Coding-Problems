/**
 * Created by daniel on 6/20/16.
 */
public class MaxSubArrayProblem {

    static int[] bruteForceMaxSubarray(int[] a, int low, int high) {
        int[] result = {Integer.MIN_VALUE, 0, 0};
        for (int i = low; i < high; i++) {
            int current_sum = 0;
            for (int j = i; j < high; j++) {
                current_sum += a[j];
                if (result[0] < current_sum) {
                    // max sum
                    result[1] = i;
                    // left index of max sum
                    result[2] = j + 1;
                    // right index of max sum
                    result[0] = current_sum;
                }
            }
        }
        return result;
    }

    static int[] findMaxCrossingSubarray(int[] a, int low, int mid, int high) {
        int sum = 0, left_sum = Integer.MIN_VALUE, right_sum = Integer.MIN_VALUE;
        int[] result = new int[3];
        // left sub array, summing the values down to low
        for (int i = mid - 1; i >= low; i--) {
            sum += a[i];
            if (sum > left_sum) {
                left_sum = sum;
                // left index of max value
                result[1] = i;
            }
        }

        sum = 0;
        // right sub array, summing the values up to high
        for (int j = mid; j < high; j++) {
            sum += a[j];
            if (sum > right_sum) {
                // right index of max value
                right_sum = sum;
                result[2] = j + 1;
            }
        }
        // the total sum
        result[0] = left_sum + right_sum;
        return result;
    }

    // see bruteforce_dacMaxSubArray for comments
    static int[] DACMaxSubarray(int[] a, int low, int high) {
        // if there is one element in the sub array
        if (high == low + 1) {
            int[] result = {low, high, a[low]};
            return result;
        } else {
            int mid = (low + high) / 2;
            int[] left = DACMaxSubarray(a, low, mid);
            int[] right = DACMaxSubarray(a, mid, high);
            int[] c = findMaxCrossingSubarray(a, low, mid, high);

            return returnMaxSubArray(left, right, c);
        }
    }

    private static int[] returnMaxSubArray(int[] left, int[] right, int[] c) {
        // if the max sum of the left array is greatest of all
        if (left[0] >= right[0] && left[0] >= c[0]) {
            return left;
            // if the max sum of the RIGHT array is greatest of all
        } else if (right[0] >= left[0] && right[0] >= c[0]) {
            return right;
            // otherwise return the max crossing sub array
        } else {
            return c;
        }
    }

    static int maxSubArray(int A[]) {
        int cursum;
        int max = cursum = A[0];
        for (int i = 1; i < A.length; i++) {
            // assuming the array contains at least one positive number,
            // if the sum goes below zero, there is no way that
            // that sum is the greatest sum. If A contains all - numbers then,
            // this will return the negative number with the smallest abs value
            cursum = cursum > 0 ? (A[i] + cursum) : A[i];
            // update the current max if cursum is greater
            max = Math.max(max, cursum);
        }
        return max;
    }

    static int[] bruteforce_dacMaxSubArray(int[] a, int low, int high) {
        // if there is less than the 35 elements in the array
        // happens when dac has broken down the problem sufficiently
        if (high - low < 35) {
            // run the brute force algorithm
            return bruteForceMaxSubarray(a, low, high);
        } else {
            // run the dac algorithm until the problem size is sufficiently small
            int mid = (low + high) / 2;
            // find max sum of left array
            int[] left = bruteforce_dacMaxSubArray(a, low, mid);
            // find max sum of right array
            int[] right = bruteforce_dacMaxSubArray(a, mid, high);
            // find max sum of crossing array
            int[] c = findMaxCrossingSubarray(a, low, mid, high);

            // check which array sum is greatest (left, right, or crossover)
            // and return the array containing the start and index of that sum as
            // well as the max sum
            return returnMaxSubArray(left, right, c);
        }
    }
}
