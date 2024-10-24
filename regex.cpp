// #include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

using namespace std;

int main(void)
{
    ifstream st("sample.txt");
    string sstring((istreambuf_iterator<char>(st)), istreambuf_iterator<char>());

    regex pattern("^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$", regex_constants::multiline); // needs C++17
    smatch results;
    string str = sstring;
    size_t offset = 0;
    while (regex_search(str, results, pattern)) {
        cout << results[0].str() << endl;
        cout << results[1].str() << endl;
        cout << offset + results.position(1) << endl;
        cout << offset + results.position(1) + results.length(1) << endl;
        cout << endl;
        str = str.substr(results[0].str().length());
        offset += results[0].str().length();
    }

    regex pattern1("bob$", regex_constants::multiline); // needs C++17
    cout << regex_replace(sstring, pattern1, "alice") << endl;

    regex pattern2("hello[0-9]+world");
    cout << boolalpha << regex_match("hello42world", pattern2) << endl;
    regex pattern3("^he[^A-Z]*\\d{2}wo\\w{2,}$");
    cout << boolalpha << regex_match("hello42world", pattern3) << endl;
    string str2 = "Words, words, words.";
    regex pattern4("\\W+");
    // iter can be dereferenced and incremented like an array
    sregex_token_iterator iter(str2.begin(), str2.end(), pattern4, -1);
    sregex_token_iterator end;
    vector<string> match_array = {iter, end};
    // vector<string> match_array;
    // copy(iter, end, back_inserter(match_array));
    for (string match_string : match_array) {
        cout << match_string << endl;
    }

    return 0;
}
