import java.util.Scanner;

public class Solution {
    static String[] vowels = new String[]{"A", "E", "I", "O", "U", "a", "e", "i", "o", "u"};

    private static String getRuler(String kingdom) {
        // TODO: implement this method to determine the ruler name, given the kingdom.
        String ruler = "";

        if(kingdom.endsWith("Y") || kingdom.endsWith("y")) {
            ruler = "nobody";
        }

        if(ruler.isEmpty()) {
            for (String vowel : vowels) {
                if (kingdom.endsWith(vowel)) {
                    ruler = "Alice";
                    break;
                }
            }
        }

        if(ruler.isEmpty()) {
            ruler = "Bob";
        }

        return ruler;
    }

    public static void main(String[] args) {
        try (Scanner in = new Scanner(System.in)) {
            int T = in.nextInt();

            for (int t = 1; t <= T; ++t) {
                String kingdom = in.next();
                System.out.println(
                        "Case #" + t + ": " + kingdom + " is ruled by " + getRuler(kingdom) + ".");
            }
        }
    }
}