import edu.evansdaniel.collections.SortingUtils;

/**
 * Created by daniel on 6/20/16.
 */
public class Benchmark {

    static long time = 0;
    static int iters = 99999;

    static int[] g = {18, 20, 12, 34
            , 18, 20, 12, 34, 18, 20, 12, 34, 18, 20, 12, 34,
            18, 20, 12, 34
            , 18, 20, 12, 34, 18, 20, 12, 34, 18, 20, 12, 34,
            18, 20, 12, 34
            , 18, 20, 12, 34, 18, 20, 12, 34, 18, 20, 12, 34,
            18, 20, 12, 34
            , 18, 20, 12, 34, 18, 20, 12, 34, 18, 20, 12, 34,
            18, 20, 12, 34
            , 18, 20, 12, 34, 18, 20, 12, 34, 18, 20, 12, 34,
            18, 20, 12, 34
            , 18, 20, 12, 34, 18, 20, 12, 34, 18, 20, 12, 34};

    public static void main(String[] args) {

        benchmark();
    }

    public static void benchmark() {
        System.out.println(g.length + " element array performed "
                + iters + " times : \n\n");

        time = System.currentTimeMillis();


        int k = 0;
        for (int i = 0; i < iters; ++i)
            // -> add function here
            k = OrderStatistics.randomizedSelect(g, 0, g.length - 1, 1);

        System.out.println(k);

        System.out.println("RandomizedSelect O(n) expected : " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");

        time = System.currentTimeMillis();

        for (int i = 0; i < iters; ++i) {
            // add function here
            SortingUtils.qs(g, 0, g.length - 1);
        }
        System.out.println(g[0]);
        // divide and conquer approach is bad (or at least worse than bf)
        // for small n (n < ~999), better for big n
        System.out.println("Sorting method time n*log(n): " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");

        time = System.currentTimeMillis();

        for (int i = 0; i < iters; ++i)
            MaxSubArrayProblem.bruteforce_dacMaxSubArray(g, 0, g.length); // add function here

        System.out.println("Combo BF/DAC time: " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");

        time = System.currentTimeMillis();

        for (int i = 0; i < iters; ++i)
            MaxSubArrayProblem.maxSubArray(g);  // add function here

        System.out.println("linear O(n) : " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");
    }
}
