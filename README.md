# Regex examples

From Wikipedia: A regular expression (shortened as regex or regexp) is a sequence of characters that specifies a match pattern in text. Basically, you can use regex patterns to efficiently find fine-tuned substring matches in strings.

Each of the examples reads the text in sample.txt and searches for matches that correspond to the regex `/^h.\D\S[a-z]{3,5}(...)\w+\d*$/m` (although the specific format of this regex differs between all of the languages). Let's break down this regex:

- `/***/m` is the overall form of a regex pattern with the multiline option enabled
    - This form may not be understood by every programming language, but is the theoretical definition
    - The multiline regex option tells the regex engine to interpret each visual line of text as its own line, rather than the entire string as one "line" of text
- `^` means the start of a line; therefore, a match must start with the letter h
- `.` means any character, so any character can follow h
- `\D` means any non-digit, so the third character in a match must not be a number
- `\S` means any non-whitespace character, so the fourth character in a match must not be whitespace (tabs or `\t`, spaces, or newlines or `\n`)
- `[a-z]{3,5}` means that between 3 to 5 (inclusive) characters in the range a-z (they must all be lowercase) must follow the fourth character
- `(...)` is what is being "captured" by this regex: the 3 characters following the `[a-z]{3,5}`
- `\w+` means one or more word characters (letters, digits, or underscores) must follow the captured characters in a match
- `\d*` means zero or more digits must follow the above one or more word characters in a match
- `$` means the end of a line

The capture group should be "mei" for both lines in sample.text, but the indices should obviously differ.

The second regex is `bob$`, which looks for lines that end with "bob". This is used to replace "bob" at the end of a line with "alice".

The third regex is `hello[0-9]+world`, which just means look anywhere in the string for "hello", then one or more digits in the range 0-9, followed by "world".

The fourth regex is `^he[^A-Z]*\d{2}wo\w{2,}$`. Aside from the meanings outlined above:

- `[^A-Z]*` means zero or more characters that are not in the range A-Z (uppercase letters)
- `\d{2}` means exactly two digits
- `\w{2,}` means two or more word characters

The fifth regex is `\W+`, which means one or more non-word characters. This is used to split a string into substrings that exclude any non-word characters (e.g. punctuation marks and whitespace).

> Note: all but the C examples use Perl regex syntax, but the C example uses POSIX ERE (extended regular expressions) syntax. This is also reflected in the GNU and BSD versions of `grep -E`, respectively. To use Perl regex syntax in C, the libpcre3 library is available.
