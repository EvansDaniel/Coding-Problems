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

    public static void insertionSort(int[] a) {
        for (int j = 1; j < a.length; ++j) {
            int key = a[j];

            int i = j - 1;
            while (i >= 0 && a[i] > key) {
                a[i + 1] = a[i];
                --i;
            }
            a[i + 1] = key;
        }
    }
}
