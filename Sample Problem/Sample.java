import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int t = in.nextInt(); // Scanner has functions to read ints, longs, strings, chars, etc.
        for (int i = 1; i <= t; ++i) {
            int n = in.nextInt();
            int m = in.nextInt();
            int candies = 0;

            for(int j = 1; j <= n; j++) {
                candies += in.nextInt();
            }

            int leftCandies = candies % m;
            
            System.out.println("Case #" + i + ": " + leftCandies);
        }
    }
}