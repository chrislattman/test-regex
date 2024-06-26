const fs = require("node:fs");

const sstring = fs.readFileSync("sample.txt").toString();
// regex literals aren't necessary but are recommended for JavaScript regex
const pattern = RegExp(/^h.\D\S[a-z]{3,5}(...)\w+\d*$/gmd);
const pattern1 = RegExp("^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$", "gmd");
if (String(pattern) !== String(pattern1)) {
    console.log("Compiled regex patterns are unequal.");
}
[...sstring.matchAll(pattern)].forEach((result) => {
    console.log(result[0]);
    console.log(result[1]);
    console.log(result.indices[1][0]);
    console.log(result.indices[1][1]);
});

console.log(sstring.replace(/bob$/gm, "alice"));

console.log(/hello[0-9]+world/.test("hello42world"));
console.log(/^he[^A-Z]*\d{2}wo\w{2,}$/.test("hello42world"));
"Words, words, words.".split(/\W+/).forEach((matchString) => {
    console.log(matchString);
});
