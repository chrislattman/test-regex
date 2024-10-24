package main

import (
	"fmt"
	"os"
	"regexp"
)

func main() {
	file, _ := os.ReadFile("sample.txt")
	sstring := string(file)
	// raw strings aren't necessary but are recommended for Go regex
	pattern := regexp.MustCompile(`(?m:^h.\D\S[a-z]{3,5}(...)\w+\d*$)`)
	pattern1 := regexp.MustCompile("(?m:^h.\\D\\S[a-z]{3,5}(...)\\w+\\d*$)")
	if (pattern.String() != pattern1.String()) {
		fmt.Println("Compiled regex patterns are unequal.")
	}
	matches := pattern.FindAllStringSubmatch(sstring, -1)
	indices := pattern.FindAllStringSubmatchIndex(sstring, -1)
	for i := range matches {
		fmt.Println(matches[i][0])
		fmt.Println(matches[i][1])
		fmt.Println(indices[i][2])
		fmt.Println(indices[i][3])
		fmt.Println()
	}

	fmt.Println(regexp.MustCompile(`(?m:bob$)`).ReplaceAllString(sstring, "alice"))

	matched, _ := regexp.MatchString(`hello[0-9]+world`, "hello42world")
	fmt.Println(matched)
	matched, _ = regexp.MatchString(`^he[^A-Z]*\d{2}wo\w{2,}$`, "hello42world")
	fmt.Println(matched)
	matchArray := regexp.MustCompile(`\W+`).Split("Words, words, words.", -1)
	for _, matchString := range matchArray {
		fmt.Println(matchString)
	}
}
