package edu.danielevans.patternmatching;

/**
 * Created by daniel on 6/26/16.
 */
public class PatternMatchingAlgos {

    public static void main(String[] args) {
        String txt = "thisisthethishellothisisthis";
        String pat = "this";
        kmpSearch(pat, txt);
    }

    public static void kmpSearch(String pat, String txt) {

        int[] lps = computeLPSArray(pat);

        int j = 0;  // index for pat[]

        int i = 0;  // index for txt[]
        while (i < txt.length()) {
            if (pat.charAt(j) == txt.charAt(i)) {
                j++;
                i++;
            }
// -----------------------------
            if (j == pat.length()) {
                System.out.printf("\nFound pattern at index %d \n", i - j);
                j = lps[j - 1];
            }
            // ------------------------------------------

            // mismatch after j matches
            else if (i < txt.length() && pat.charAt(j) != txt.charAt(i)) {
                // Do not match lps[0..lps[j-1]] characters,
                // they will match anyway
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }
    }

    private static int[] computeLPSArray(String pat) {
        int len = 0;  // length of the previous longest prefix suffix
        int i;
        int[] lps = new int[pat.length()];
        lps[0] = 0; // lps[0] is always 0
        i = 1;

        // the loop calculates lps[i] for i = 1 to M-1
        while (i < pat.length()) {
            if (pat.charAt(i) == pat.charAt(len)) {
                len++;
                lps[i] = len;
                i++;
            } else // (pat[i] != pat[len])
            {
                if (len != 0) {
                    // This is tricky. Consider the example
                    // AAACAAAA and i = 7.
                    len = lps[len - 1];

                    // Also, note that we do not increment i here
                } else // if (len == 0)
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        for (int j = 0; j < lps.length; j++) {
            System.out.print(lps[j] + " ");
        }
        return lps;
    }
}
