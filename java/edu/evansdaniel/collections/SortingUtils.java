package edu.evansdaniel.collections;

/**
 * Created by daniel on 6/23/16.
 */
public class SortingUtils {

    public static void main(String[] args) {
        int[] a = {5, 3, 6, 4, 8, 3};
        insertionSort(a);
        ms(a, 0, a.length - 1);
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + "   ");
        }
    }

    /**
     * 'new' elements are defined as a[j]
     * 'old' elements are defined as a[j-1...0]
     *
     * @param a any array
     */
    public static void insertionSort(int[] a) {
        for (int j = 1; j < a.length; ++j) {
            // save value of 'new' element
            int key = a[j];

            int i = j - 1;
            // loop through the 'old' indices
            while (i >= 0 && a[i] > key) {
                // make the next element be the current element, i.e. shift the
                // current element over; this is okay because we have saved the
                // value of the 'new' index in key
                a[i + 1] = a[i];
                // decrement i, will make it to -1
                --i;
            }
            // will 'insert' the 'new' element either at the beginning or
            // at the point where the key is greater than a[i]
            a[i + 1] = key;
        }
    }

    public static void ms(int[] a, int p, int r) {
        // if there is only one element in the sub array
        if (p < r) {
            int q = (int) Math.floor((p + r) / 2.0);
            // call mergesort on the left sub array
            ms(a, p, q);
            // call mergesort on the right sub array
            ms(a, q + 1, r);
            // call merge on the sub arrays
            m(a, p, q, r);
        }
    }

    public static void m(int[] a, int p, int q, int r) {
        // compute length of left sub array
        // n1 = 1
        int n1 = q - p + 1;
        // compute length of right sub array
        // n2 = 1
        int n2 = r - q;

        // + 1 because of the sentinel values added below
        int[] left = new int[n1 + 1];
        int[] right = new int[n2 + 1];   // both are 2 element arrays

        // copy a[p]-a[n1-1] into left
        System.arraycopy(a, p, left, 0, n1);
        // copy a[q]-a[n2-1] into right
        System.arraycopy(a, q + 1, right, 0, n2);

        // sentinel values for the left and right array
        left[n1] = Integer.MAX_VALUE;
        right[n2] = Integer.MAX_VALUE;

        // keeps track of the index into left
        int li = 0;
        // keeps track of the index into right
        int ri = 0;

        // loop through the copied sub arrays, merging them into the
        // array a. This works because the sub arrays are sorted already,
        // so that as we iterate over them, we know that a[p...k-1]
        // contains the smallest elements from the left[0...n1] and
        // right[0...n2] in sorted order
        for (int cpyArrayIndex = p; cpyArrayIndex <= r; ++cpyArrayIndex) {
            // copy the smaller current element in the left or right sub array
            // into a and increment that arrays index (either ri or li
            // if left's current value is less than right's curr value
            if (left[li] <= right[ri]) {
                a[cpyArrayIndex] = left[li];
                ++li;
            } else {
                a[cpyArrayIndex] = right[ri];
                ++ri;
            }
        }
    }

    // an alternative version of merge sort without using sentinel nodes
    static void merge(int A[], int p, int q, int r) {
        int i, j, k;

        int n1 = q - p + 1;
        int n2 = r - q;

        int[] L = new int[n1];
        int R[] = new int[n2];

        for (i = 0; i < n1; i++)
            L[i] = A[p + i];
        for (j = 0; j < n2; j++)
            R[j] = A[q + j + 1];

        for (i = 0, j = 0, k = p; k <= r; k++) {
            if (i == n1) {
                A[k] = R[j++];
            } else if (j == n2) {
                A[k] = L[i++];
            } else if (L[i] <= R[j]) {
                A[k] = L[i++];
            } else {
                A[k] = R[j++];
            }
        }
    }

    static void mergeSort(int A[], int p, int r) {
        if (p < r) {
            int q = (p + r) / 2;
            mergeSort(A, p, q);
            mergeSort(A, q + 1, r);
            merge(A, p, q, r);
        }
    }
}
