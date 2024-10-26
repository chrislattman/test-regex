use std::{fs, str};

use regex::Regex;

fn main() {
    let binding = fs::read("sample.txt").unwrap();
    let sstring = str::from_utf8(&binding).unwrap();
    // r-strings aren't necessary but are recommended for Rust regex
    let pattern = Regex::new(r"(?m:^h.\D\S[a-z]{3,5}(...)\w+\d*$)").unwrap();
    let pattern1 = Regex::new("(?m:^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$)").unwrap();
    if pattern.as_str() != pattern1.as_str() {
        println!("Compiled regex patterns are unequal.");
    }
    let mut caps = pattern.captures(sstring);
    let mut offset = 0;
    while caps.is_some() {
        let binding = caps.as_ref().unwrap();
        let mut iterator = binding.iter();
        let mut res = iterator.next();
        while res != None {
            println!("{}", res.unwrap().map(|m| m.as_str()).unwrap());
            res = iterator.next();
        }
        let mut locs = pattern.capture_locations();
        pattern.captures_read(&mut locs, sstring);
        println!("{}\n{}", offset + locs.get(1).unwrap().0, offset + locs.get(1).unwrap().1);
        offset += locs.get(0).unwrap().1 + 1; // adding 1 to skip the newline (global match includes end of line)
        caps = pattern.captures_at(sstring, offset);
        println!();
    }

    println!("{}", Regex::new(r"(?m:bob$)").unwrap().replace_all(sstring, "alice").as_ref());

    let re = Regex::new(r"hello[0-9]+world").unwrap();
    println!("{}", re.is_match("hello42world"));
    let re = Regex::new(r"^he[^A-Z]*\d{2}wo\w{2,}$").unwrap();
    println!("{}", re.is_match("hello42world"));
    let re = Regex::new(r"\W+").unwrap();
    let match_array: Vec<_> = re.split("Words, words, words.").collect();
    for match_string in match_array.into_iter() {
        println!("{}", match_string);
    }
}
