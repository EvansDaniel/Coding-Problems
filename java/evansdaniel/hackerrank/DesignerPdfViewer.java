package evansdaniel.hackerrank;

/**
 * Created by daniel on 8/23/16.
 *
 * @author Daniel Evans
 * Question Prompt: https://www.hackerrank.com/contests/101hack40/challenges/designer-pdf-viewer
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DesignerPdfViewer {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File(Config.getDataDir() + "DesignerPdfViewerData.txt"));
        int h[] = new int[26];
        for (int h_i = 0; h_i < 26; h_i++) {
            h[h_i] = in.nextInt();
        }
        String word = in.next();
        int height = h[word.charAt(0) - 'a'];

        for (int i = 1; i < word.length(); i++) {
            if (height < h[word.charAt(i) - 'a']) {
                height = h[word.charAt(i) - 'a'];
            }
        }
        System.out.println(height * word.length());
    }
}