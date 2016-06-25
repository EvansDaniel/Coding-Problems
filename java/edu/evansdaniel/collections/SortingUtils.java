package edu.evansdaniel.collections;

import java.util.Random;

/**
 * Created by daniel on 6/23/16.
 */
public class SortingUtils {

    public static void main(String[] args) {
        int[] a = {7, 8, 6, 10, 15, 36, 28, 68, 365, 57, 24, 1, 5, 33, 8, 2, 89, 37};
//        insertionSort(a);
//        ms(a, 0, a.length - 1);
        a = countingSort(a);
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + "   ");
        }
    }

    /**
     * @param a any array
     * @return index of maximum element in a
     */
    private static int max(int[] a) {
        int maxI = 0;
        for (int i = 1; i < a.length; i++) {
            if (a[maxI] < a[i])
                maxI = i;
        }
        return maxI;
    }

    /**
     * @param a any array
     * @return sorted array
     */
    public static int[] countingSort(int[] a) {
        // get the max element in a, add one to prevent arrayIndexOutOfBounds
        int maxInA = a[max(a)] + 1;

        // count: array that will contain the # of times a[k] appears in
        // array a, where 0 <= k <= a.length
        int[] count = new int[maxInA];
        // sorted: the array returned after building the sorted version of a
        int[] sorted = new int[a.length];

        // count the number of times the values in a appear in a
        // record them in count at index valueInA
        for (int valueInA : a) {
            ++count[valueInA];
        }
        /**
         * starts at i = 1 because it adds count[i-1], count[0] will have nothing added to it
         */
        for (int i = 1; i < count.length; ++i) {
            // add the previous element in count to the current
            count[i] += count[i - 1];
            // count[i]: # of elements <= to i
        }
        for (int j = a.length - 1; j >= 0; --j) {
            // put element a[j] at the index in sorted = to
            // the (# of elements-1) in a that are less than a[j]
            sorted[count[a[j]] - 1] = a[j];

            // if there are subsequent elements in a = to a[j] this will
            // cause them to placed at count[a[j]-1, 1 behind where a[j] was placed
            count[a[j]] = count[a[j]] - 1; // > 0 if there is more than 1 element in a = to a[j]
        }
        return sorted;
    }

    /**
     * 'new' elements are defined as a[j]
     * 'old' elements are defined as a[j-1...0]
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

    // http://www.java2novice.com/java-sorting-algorithms/merge-sort/
    // good diagram at this link
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
        int li, ri, k;

        int n1 = q - p + 1;
        int n2 = r - q;

        int[] L = new int[n1];
        int R[] = new int[n2];

        // copy the left sub array of a into L
        for (li = 0; li < n1; li++)
            L[li] = A[p + li];
        // copy right sub array of a into
        for (ri = 0; ri < n2; ri++)
            R[ri] = A[q + ri + 1];

        // while the index into a <= to the end of the array a (r)
        for (li = 0, ri = 0, k = p; k <= r; k++) {
            // if the index into the left (L) sub array is equal to L.length
            if (li == n1) {
                A[k] = R[ri++];
                // if the index into the right (R) sub array is equal to R.length
            } else if (ri == n2) {
                A[k] = L[li++];
                // if the current element in L is <= to the current element in R
            } else if (L[li] <= R[ri]) {
                // copy L's current element to A
                A[k] = L[li++];
            } else {
                // copy R's element to A
                A[k] = R[ri++];
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


    /**
     * One common approach is the median-of-3 method: choose
     * the pivot as the median (middle element) of a set of 3 elements randomly selected
     * from the subarray
     *
     * @param a     any array
     * @param start start index into the array
     * @param end   end index into the array
     */
    public static void qs(int[] a, int start, int end) {
        if (start < end) {
            int q = randPartition(a, start, end);
            qs(a, start, q - 1);
            qs(a, q + 1, end);
        }
    }

    public static int randPartition(int[] a, int start, int end) {
        Random r = new Random();
//        int pivot = start + r.nextInt(end-start+1);
        // the formula: start + Math.floor(Math.random()*(end-start+1))
        // ensures we end up in the range [start,end]
        // take the case of start = 9, end = 11 -> range = [9,11]
        // that is, 9 + floor((0.0 - .9999) * (11-9+1  == 3),
        // which boils down to 9 + (0-2)
        int pivot = (int) (start + Math.floor(Math.random() * (end - start + 1)));
        swap(a, pivot, end);
        return partition(a, start, end);
    }

    /**
     * Loop Invariant:
     * At the beginning of each iteration of the loop of lines 3–6, for any array
     * index k,
     * if k is less than the lastKnownElementLessThanPivot, its value is less than the pivot
     * 1. If p <= k <= lastKnownElementLessThanPivot, then a[k] <= x.
     * <p>
     * if k is greater than the lastKnownElementLessThanPivot, then its value is
     * > than the pivot element
     * 2. If lastKnownElementLessThanPivot + 1 <= k <= j - 1, then a[k] > x.
     * <p>
     * if k is = to the index of x, then k's value is = to x
     * 3. If k = end, then A[k] = x.
     *
     * @param a   any array
     * @param p   start index
     * @param end end index
     * @return the index of the pivot element
     */
    public static int partition(int[] a, int p, int end) {
        // pivot is the element that is being compared against;
        // a good pivot will split the array in half
        int pivot = a[end];
        int lastKnownElementLessThanPivot = p - 1;
        // j represents the current element that is being iterated through
        int j;
        for (j = p; j < end; ++j) {
            // to sort in decreasing order, flip the >= sign to <=
            if (a[j] <= pivot) {
                // increment the last known element
                ++lastKnownElementLessThanPivot;
                // swap that value with the current element
                swap(a, lastKnownElementLessThanPivot, j);
            }
        }
        // swap pivot with the the element just after the last known
        // element less than the pivot
        swap(a, lastKnownElementLessThanPivot + 1, end);
        // if all the elements in a are equal
        if (lastKnownElementLessThanPivot == j)
            return (int) Math.floor((p + end) / 2);

        return lastKnownElementLessThanPivot + 1;
    }

    private static void swap(int[] a, int x, int j) {

        int tmp = a[x];
        a[x] = a[j];
        a[j] = tmp;
    }

    private static void swap(Interval[] a, int x, int j) {

        Interval tmp = a[x];
        a[x] = a[j];
        a[j] = tmp;
    }

    // TODO: p. 189 fuzzy sorting
    // TODO: fix fuzzy sort
    public static void fuzzySort(Interval[] a, int start, int end) {
        if (start < end) {
            Interval pivot = fuzzyPartition(a, start, end);
            fuzzySort(a, start, pivot.left);
            fuzzySort(a, pivot.right, end);
        }
    }

    // TODO: fix fuzzy partition
    private static Interval fuzzyPartition(Interval[] a, int start, int end) {

        // Pick a random interval as a pivot
        int pivot = (int) (start + Math.floor(Math.random() * (end - start + 1)));
        swap(a, pivot, end);
        Interval intersection = a[end];

        // Find an intersection of the pivot and other intervals
        for (int i = start; i < end; ++i) {
            // a.left <= b.right && b.left <= a.right;
            if (intersects(intersection, a[i])) {
                // get rid of ifs ??? always true ????
                if (a[i].left > intersection.left)
                    intersection.left = a[i].left;
                if (a[i].right < intersection.right)
                    intersection.right = a[i].right;
            }
        }
        int s;
        for (int i = s = start; i < end; ++i) {
            if (before(a[i], intersection)) {
                swap(a, i, intersection);
                ++s;
            }
        }
        swap(a, end, s);
        int t, i;
        // Group intervals including the intersection
        for (t = s + 1, i = end; t <= i; ) {
            if (intersects(a[i], intersection)) {
                swap(a, t, i);
                ++t;
            } else {
                --i;
            }
        }

        return new Interval(s, t + 1);
    }

    private static boolean before(Interval a, Interval b) {
        return a.left <= b.right && b.left <= a.right;
    }

    private static void swap(Interval[] a, int i, Interval intersection) {

    }

    private static boolean intersects(Interval a, Interval b) {

        return a.left <= b.right && b.left <= a.right;
    }
}
