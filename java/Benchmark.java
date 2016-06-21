/**
 * Created by daniel on 6/20/16.
 */
public class Benchmark {

    static long time = 0;
    static int iters = 999999;

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


        for (int i = 0; i < iters; ++i)
            AOA.bruteForceMaxSubarray(g, 0, g.length); // -> add function here

        // Let n == g.length
        // brute force is good for very small n (n < ~35), very bad for large n
        System.out.println("Brute force O(n^2) : " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");

        time = System.currentTimeMillis();

        for (int i = 0; i < iters; ++i)
            AOA.DACMaxSubarray(g, 0, g.length); // add function here
        // divide and conquer approach is bad (or at least worse than bf)
        // for small n (n < ~999), better for big n
        System.out.println("DAC time O(n*lg(n)): " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");

        time = System.currentTimeMillis();

        for (int i = 0; i < iters; ++i)
            AOA.bruteforce_dacMaxSubArray(g, 0, g.length); // add function here

        System.out.println("Combo BF/DAC time: " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");

        time = System.currentTimeMillis();

        for (int i = 0; i < iters; ++i)
            AOA.maxSubArray(g);  // add function here

        System.out.println("linear O(n) : " +
                String.valueOf(System.currentTimeMillis() - time) + " ms\n");
    }
}
