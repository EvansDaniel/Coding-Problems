/**
 * Created by daniel on 6/20/16.
 */
public class AOA {

    // debugging needed
    static int[] findMaxCrossingSubarray(int[] a, int low, int mid, int high) {
        int ls = -999999999;
        int sum = 0;
        int maxLeft = 0;
        for (int i = mid; i >= low; --i) {
            sum += a[i];
            if (sum > ls) {
                ls = sum;
                maxLeft = i;
            }
        }
        int rs = -9999999;
        sum = 0;
        int maxRight = 0;
        for (int i = mid + 1; i < high; i++) {
            sum += a[i];
            if (sum > rs) {
                rs = sum;
                maxRight = i;
            }
        }
        int[] maxCrossArr = new int[3];
        maxCrossArr[0] = maxLeft;
        maxCrossArr[1] = maxRight;
        maxCrossArr[2] = ls + rs;
        return maxCrossArr;
    }

    // need to debug -> divide and conquer for maximum sub array problem
    static int[] findMaxSubarray(int[] a, int low, int high) {
        if (high == low) {
            int[] maxSubarray = new int[3];
            maxSubarray[0] = low;
            maxSubarray[1] = high;
            maxSubarray[2] = a[low];
            return maxSubarray;
        } else {
            int[] rightMax;
            int[] leftMax;
            int[] crossMax;
            int mid = (int) (Math.floor(low + high / 2.0));
            leftMax = findMaxSubarray(a, low, mid);

            rightMax = findMaxSubarray(a, mid + 1, high);

            crossMax = findMaxCrossingSubarray(a, low, mid, high);

            if (leftMax[2] >= rightMax[2] && leftMax[2] >= crossMax[2])
                return leftMax;
            else if (rightMax[2] >= leftMax[2] && rightMax[2] >= crossMax[2])
                return rightMax;
            else
                return crossMax;
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
}
