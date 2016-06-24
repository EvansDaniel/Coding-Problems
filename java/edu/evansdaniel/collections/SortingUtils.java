package edu.evansdaniel.collections;

/**
 * Created by daniel on 6/23/16.
 */
public class SortingUtils {

    public static void main(String[] args) {
        int[] a = {13, 42, 45, 859, 385, 194, 5683, 48};
        insertionSort(a);
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
}
