import java.util.Arrays;

/**
 * Created by Daniel Evans on 4/2/2016.
 *
 * This program checks if any
 * anagram of a string1 is contained
 * in any substring of string2
 * 
 */
public class AnagramsSorted {

    public static void check(String s, String t) {

        int len = s.length();
        boolean found = false;
        s = sort(s);
        for (int i =0; i+len-1< t.length(); i++) {
            String temp = t.substring(i, i + len);
            //System.out.print(temp);
            temp = sort(temp);
            if (s.equals(temp)) {
                found = true;
                System.out.println("YES");
                break;
            }
        }
        if(!found) {
            System.out.println("NO");
        }
    }
    public static String sort(String t) {

        char[] temp = t.toCharArray();
        Arrays.sort(temp);
        String orig = "";
        for( int i =0; i< temp.length; i++) {
            orig += new Character(temp[i]).toString();
            //System.out.print(temp[i]);


        }
        //System.out.println(orig);
        return orig;
    }

    public static void main(String[] args) {

        check("DZ","JeWLkJFHCQvLIUxEZcZcUSHiOrrudBmdtQafDAgihGIGdf" );

    }
}
