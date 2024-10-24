import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Regex {
    public static void main(String[] args) throws IOException {
        String sstring = new String(Files.readAllBytes(Paths.get("sample.txt")), StandardCharsets.UTF_8);
        Pattern pattern = Pattern.compile("^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$", Pattern.MULTILINE);
        // Pattern pattern = Pattern.compile("(?m:^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$)");
        Matcher matcher = pattern.matcher(sstring);
        while (matcher.find()) {
            System.out.println(matcher.group(0));
            System.out.println(matcher.group(1));
            System.out.println(matcher.start(1));
            System.out.println(matcher.end(1));
            System.out.println();
        }

        System.out.println(sstring.replaceAll("(?m:bob$)", "alice"));

        System.out.println(Pattern.matches("hello[0-9]+world", "hello42world"));
        System.out.println(Pattern.matches("^he[^A-Z]*\\d{2}wo\\w{2,}$", "hello42world"));
        String[] matchArray = "Words, words, words.".split("\\W+");
        // String[] matchArray = Pattern.compile("\\W+").split("Words, words, words.");
        for (String matchString : matchArray) {
            System.out.println(matchString);
        }
    }
}
