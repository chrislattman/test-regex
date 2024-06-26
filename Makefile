OS=$(shell uname)
ifneq ($(findstring MINGW64_NT,$(OS)),)
C_LIB=-lregex
endif

java:
	java Regex.java

python:
	python3 regex.py

nodejs:
	node regex.js

go:
	go run go/regex.go

c:
	gcc -Wall -Wextra -Werror -pedantic -std=c99 -o regex regex.c $(C_LIB) && ./regex

rust:
	cargo run -q

clean:
	rm -rf regex target

.PHONY: java python nodejs go c rust
