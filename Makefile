java:
	java Regex.java

python:
	python3 regex.py

nodejs:
	node regex.js

go:
	go run go/regex.go

c:
	gcc -Wall -Wextra -Werror -pedantic -std=c99 -o regex regex.c && ./regex

rust:
	cargo run -q

clean:
	rm -rf regex target

.PHONY: java python nodejs go c rust
