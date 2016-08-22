import java.io.*;
import java.util.*;

public class FunnyString {

    public static void main(String[] args) {
      Scanner scan = new Scanner(System.in);
      int numRows = scan.nextInt();
      // loop through rows 
      for(int i =0; i < numRows; ++i) {
        String row = scan.next();
        int end = row.length();
        boolean isFunny = true;
        for(int j=1; j<row.length()/2+1; ++j) {
          if(Math.abs(row.charAt(j) - row.charAt(j-1))
            != Math.abs(row.charAt(end-j) - row.charAt(end-j-1))) {
              isFunny = false;
              break;
          }
        }
        System.out.println(isFunny ? "Funny" : "Not Funny");
      }
    }
}
