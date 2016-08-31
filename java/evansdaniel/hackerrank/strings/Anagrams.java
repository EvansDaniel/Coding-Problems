package evansdaniel.hackerrank.strings;

/**
 * Created by Daniel Evans on 4/2/2016.
 */
public class Anagrams {

    public static String removeChar(String s, int index) {
        String temp;
        // could use replace string method
        temp = s.substring(0,index) + s.substring(index+1, s.length());

        return temp;
    }

    public static int countOccurrences(String s, char a) {
        int count = 0;
        String temp = s;
        for(int i =0; i<temp.length();) {
            if(temp.charAt(i) == a) {

                // don't increment i because we need to check the current index (i) of the newly created
                // string for the character a
                count++;
                // delete this instance of character a
                temp = removeChar(temp,i);

            }
            else {
                i++;
            }
        }
        return count;
    }

    public static boolean isAnagram(String s, String t) {


        // if they strings aren't the same length they can't be anagrams
        if(s.length() != t.length()) {
            return false;
        }

        // count the occurrences of the charAt index i of s and see if it equals
        // the # of occurrences of charAt index i of t
        for(int i =0; i<s.length(); i++) {
            if(countOccurrences(s,s.charAt(i)) != countOccurrences(t,s.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        System.out.println(isAnagram("nagaram","anagram"));
    }
}