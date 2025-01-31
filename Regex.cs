using System.Text.RegularExpressions;

string sstring = File.ReadAllText("sample.txt");
string pattern = "(?m:^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$)";
foreach (Match match in Regex.Matches(sstring, pattern))
{
    Console.WriteLine(match.Groups[0].ToString());
    Console.WriteLine(match.Groups[1].ToString());
    Console.WriteLine(match.Groups[1].Index);
    Console.WriteLine(match.Groups[1].Index + match.Groups[1].Length);
    Console.WriteLine();
}

Console.WriteLine(MyRegex().Replace(sstring, "alice"));

Console.WriteLine(MyRegex1().IsMatch("hello42world"));
Console.WriteLine(MyRegex2().IsMatch("hello42world"));
string[] matchArray = MyRegex3().Split("Words, words, words.");
foreach (string match in matchArray)
{
    Console.WriteLine(match);
}

partial class Program
{
    [GeneratedRegex("(?m:bob$)")]
    private static partial Regex MyRegex();
}

partial class Program
{
    [GeneratedRegex("hello[0-9]+world")]
    private static partial Regex MyRegex1();
}

partial class Program
{
    [GeneratedRegex("^he[^A-Z]*\\d{2}wo\\w{2,}$")]
    private static partial Regex MyRegex2();
}

partial class Program
{
    [GeneratedRegex("\\W+")]
    private static partial Regex MyRegex3();
}
