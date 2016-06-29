import edu.evansdaniel.collections.SortingUtils;

/**
 * Created by daniel on 6/27/16.
 */
public class OrderStatistics {

    public static void main(String[] args) {
        int[] a = {1, 5, 3, 10, 45, 6, 7};
//        SortingUtils.arrayShuffle(a);
        int ith = 2;
        System.out.println("a[ith=" + ith + "] = " + selectIth(a, 0, a.length - 1, ith));
//        selectIth(a,0,a.length-1,ith);
    }

    /**
     * get the median of some array
     *
     * @param a      any array
     * @param end    the index of last element in range
     * @param numEPA num elements in the split arrays
     * @return median of the array
     */
    public static int getMedian(int[] a, int end, int numEPA) {

        int[] medians = new int[end / numEPA + 1];
        int j = 0;
        for (int i = numEPA / 2; j < medians.length; ) {
            medians[j++] = a[i];
            if (i + numEPA >= a.length)
                i = (i + (numEPA / 2) + (a.length % 5))/*a.length)/2*/;
            else
                i += numEPA - 1;
            System.out.println("i = " + i);
        }
        for (int i = 0; i < medians.length; i++) {
            System.out.println(medians[i]);
        }
        // (medians.length-1)/2 provides the median value of medians
        // every time
        return randomizedSelect(medians, 0, medians.length - 1, (medians.length - 1) / 2);
    }

    // TODO: NOT WORKING
    public static int selectIth(int[] a, int start, int end, int ith) {
        // at most NUMEPA Elements Per Array
        int NUMEPA = 5;
        validateSelect(a, start, end, ith);
        if (a.length <= NUMEPA)
            throw new IllegalStateException("a.length must be at least 6 " +
                    "a.length = " + a.length);
        // - END EXCEPTIONS CHECKING -------
        if (end - start <= 0)
            return a[start];

        a = splitArray(a, start, end, NUMEPA);
        int mOfM = getMedian(a, end, NUMEPA);
        System.out.println("mom " + mOfM);
        int pivotIndex = SortingUtils.partition(a, start, end/*a.length-1*/, mOfM);
        for (int i = 0; i < a.length; ++i) {
            System.out.print(a[i] + " ");
        }
        System.out.println("a[pi] " + a[pivotIndex]);
        System.out.println("pi " + pivotIndex);
        int k = pivotIndex - start + 1;
        if (k == ith)
            return a[pivotIndex];
        else if (ith < k)
            return selectIth(a, start, pivotIndex - 1, ith);
        else
            // we must subtract pivotIndex's ith placement out
            // of ith
            return selectIth(a, pivotIndex + 1, end, ith - k);
    }

    /**
     * "splits" (see return) a into floor(n/numEPA) arrays with numEPA elements
     *
     * @param a      any array
     * @param numEPA number of elements per array
     * @return an array with Math.floor(n/numEPA) sections of
     * numEPA elements, each section is sorted
     */
    public static int[] splitArray(int[] a, int start, int end, int numEPA) {
        // possibly divide num epa by 2 each call to selectIth

        for (int i = start; i < end; ) {
            int to = (i + numEPA > end) ? (end % numEPA) : numEPA;
            SortingUtils.insertionSort(a, i, i + to);
            i += to;
        }
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + " ");
        }
        System.out.println();
        return a;
    }

    /**
     * runs in an expected O(n) time, but worst case of O(n^2)
     *
     * @param a     any array
     * @param start beginning part at least 0
     * @param end   end part of the array, at most a.length-1
     * @param ith   index of the ith smallest element in the array
     * @return
     */
    public static int randomizedSelect(int[] a, int start, int end, int ith) {
        validateSelect(a, start, end, ith);
        //----- END EXCEPTIONS CHECKING -------------
        if (end - start <= 0)
            return a[start];

        // value at pivot index is "sorted" in a
        int pivotIndex = SortingUtils.randPartition(a, start, end);

        // k represents the distance from the start of
        // the subarray pivotIndex's sorted position+1.
        // (i.e. pivotIndex's ith placement)

        // pivotIndex's range -> [0,a.length-1]
        // map pivotIndex onto ith's range -> [1,a.length]
        // k goes from [1,a.length]
        // k is also always 1 more than the # of elements on the low
        // side of the pivotIndex
        int k = pivotIndex - start + 1;
        if (ith == k)
            return a[pivotIndex];
        else if (ith < k)
            return randomizedSelect(a, start, pivotIndex - 1, ith);
        else
            // we must subtract pivotIndex's ith placement out
            // of ith
            return randomizedSelect(a, pivotIndex + 1, end, ith - k);
    }

    private static void validateSelect(int[] a, int start, int end, int ith) {
        if (a == null)
            throw new NullPointerException("a cannot be null");
        if (ith > a.length || ith < 0)
            throw new IllegalArgumentException("ith must be in the range" +
                    "0 < ith < a.length. ith = " + ith);
        if (start < 0)
            throw new IllegalArgumentException("start is less than 0 -> " + start);
        if (end >= a.length)
            throw new IllegalArgumentException("end >= a.length. a.length: " + a.length
                    + " end = " + end);
    }

}
