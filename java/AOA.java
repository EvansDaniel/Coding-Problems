/**
 * Created by daniel on 6/20/16.
 */
public class AOA {

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

    // debugging needed
    static int[] findMaxCrossingSubarray(int[] a, int low, int mid, int high) {
        int sum = 0, left_sum = Integer.MIN_VALUE, right_sum = Integer.MIN_VALUE;
        int[] result = new int[3];
        for (int i = mid - 1; i >= low; i--) {
            sum += a[i];
            if (sum > left_sum) {
                left_sum = sum;
                // left index of max value
                result[1] = i;
            }
        }

        sum = 0;

        for (int j = mid; j < high; j++) {
            sum += a[j];
            if (sum > right_sum) {
                right_sum = sum;
                // right index of max value
                result[2] = j + 1;
            }
        }
        // the total sum
        result[0] = left_sum + right_sum;
        return result;
    }

    // need to debug -> divide and conquer for maximum sub array problem
    static int[] DACMaxSubarray(int[] a, int low, int high) {
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
        if (left[0] >= right[0] && left[0] >= c[0]) {
            return left;
        } else if (right[0] >= left[0] && right[0] >= c[0]) {
            return right;
        } else {
            return c;
        }
    }

    static int maxSubArray(int A[]) {
        int cursum;
        int max = cursum = A[0];
        for (int i = 1; i < A.length; i++) {
            cursum = cursum > 0 ? (A[i] + cursum) : A[i];
            max = Math.max(max, cursum);
        }
        return max;
    }

    static int[] bruteforce_dacMaxSubArray(int[] a, int low, int high) {
        if (high - low < 35) {
            return bruteForceMaxSubarray(a, low, high);
        } else {
            int mid = (low + high) / 2;
            int[] left = bruteforce_dacMaxSubArray(a, low, mid);
            int[] right = bruteforce_dacMaxSubArray(a, mid, high);
            int[] c = findMaxCrossingSubarray(a, low, mid, high);

            return returnMaxSubArray(left, right, c);
        }
    }
}
