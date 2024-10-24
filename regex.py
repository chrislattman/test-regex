import re

sstring = open("sample.txt").read()
# r-strings aren't necessary but are recommended for Python regex
pattern = re.compile(r"^h.\D\S[a-z]{3,5}(...)\w+\d*$", re.MULTILINE)
pattern1 = re.compile("^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$", re.MULTILINE)
if str(pattern) != str(pattern1):
    print("Compiled regex patterns are unequal.")
# pattern = re.compile(r"(?m:^h.\D\S[a-z]{3,5}(...)\w+\d*$)")
for result in pattern.finditer(sstring):
    print(result.group(0))
    print(result.group(1))
    print(result.start(1))
    print(result.end(1))
    print()

print(re.sub(r"(?m:bob$)", "alice", sstring))

print(re.search(r"hello[0-9]+world", "hello42world") is not None)
print(re.search(r"^he[^A-Z]*\d{2}wo\w{2,}$", "hello42world") is not None)
match_array = re.split(r"\W+", "Words, words, words.")
for match_string in match_array:
    print(match_string)
