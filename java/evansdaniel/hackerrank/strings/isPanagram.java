package evansdaniel.hackerrank.strings;

import java.util.BitSet;
import java.util.Scanner;

/**
 * Created by Daniel Evans on 4/7/2016.
 */

/*

 For any string read from System.in, this program will tell
 you if the string is a panagram (a string of letters that has
 contains all of the letters in the alphabet)

 The program is case-insensitive and ignores spaces
 */
public class isPanagram {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        // get nextline
        char[] a = sc.nextLine().replace("\\s+","").toLowerCase().toCharArray();
        // a bit set is a dynamically expanding array
        // that sets its values with bits (true || false values)
        BitSet b = new BitSet();

        for(char c: a){
            // if the character is in the alphabet
            if(c >='a' && c<='z'){
                // set it at the proper index of the array
                // ex: c='b', then store 'b' at index 1; c='c', then store 'c' at index 2
                b.set(c-'a');
            }
        }
        // cardinality is the # of values in the bitset that are true
        System.out.println(b.cardinality()==26?"pangram":"not pangram");
    }
}
