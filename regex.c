#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(void)
{
    struct stat statbuf;
    char *string = NULL, *cursor, *global, *match, *new_string = NULL, *words = "Words, words, words.";
    FILE *fp;
    int status;
    regex_t pattern;
    size_t string_size, cursor_length;
    regmatch_t indices_2[2], indices_1[1];
    regoff_t offset, old_offset;

    stat("sample.txt", &statbuf);
    string = malloc(statbuf.st_size);
    fp = fopen("sample.txt", "r");
    fread(string, sizeof(char), statbuf.st_size, fp);
    fclose(fp);

    regcomp(&pattern, "^h.[[:alpha:][:punct:][:space:]][[:graph:]][[:lower:]]{3,5}(...)[[:graph:]]+[[:digit:]]*$", REG_EXTENDED | REG_NEWLINE);
    string_size = strlen(string) + 1;
    global = malloc(string_size);
    match = malloc(string_size);
    cursor = string;
    offset = 0;
    status = regexec(&pattern, cursor, 2, indices_2, 0);
    while (status == 0) {
        strcpy(global, cursor);
        global[indices_2[0].rm_eo] = '\0';
        printf("%s\n", global);
        strcpy(match, cursor + indices_2[1].rm_so);
        match[indices_2[1].rm_eo - indices_2[1].rm_so] = '\0';
        printf("%s\n", match);
        printf("%lld\n%lld\n", indices_2[1].rm_so + offset, indices_2[1].rm_eo + offset);
        offset += indices_2[0].rm_eo + 1; // adding 1 to skip the newline (global match includes end of line)
        cursor += offset;
        status = regexec(&pattern, cursor, 2, indices_2, 0);
    }
    free(match);
    free(global);
    regfree(&pattern);

    regcomp(&pattern, "bob$", REG_EXTENDED | REG_NEWLINE);
    cursor = string;
    status = regexec(&pattern, cursor, 1, indices_1, 0);
    while (status == 0) {
        if (new_string == NULL) {
            offset = indices_1[0].rm_eo + 2; // to accommodate for alice which is 2 characters longer than bob
            new_string = malloc(offset);
            strncpy(new_string, cursor, indices_1[0].rm_so);
            strcpy(new_string + indices_1[0].rm_so, "alice");
        } else {
            old_offset = offset;
            offset += indices_1[0].rm_eo + 2; // to accommodate for alice which is 2 characters longer than bob
            new_string = realloc(new_string, offset);
            strncpy(new_string + old_offset, cursor, indices_1[0].rm_so);
            strcpy(new_string + old_offset + indices_1[0].rm_so, "alice");
        }
        cursor += indices_1[0].rm_eo;
        status = regexec(&pattern, cursor, 1, indices_1, 0);
    }
    cursor_length = strlen(cursor);
    if (cursor_length > 0) {
        new_string = realloc(new_string, offset + cursor_length + 1);
        strcpy(new_string + offset, cursor);
    }
    printf("%s\n", new_string);
    free(new_string);
    regfree(&pattern);

    regcomp(&pattern, "hello[[:digit:]]+world", REG_EXTENDED | REG_NOSUB);
    status = regexec(&pattern, "hello42world", 0, NULL, 0);
    printf("%s\n", status == 0 ? "true" : "false");
    regfree(&pattern);

    regcomp(&pattern, "^he[[:lower:]]*[[:digit:]]{2}wo[[:alnum:]]{2,}$", REG_EXTENDED | REG_NOSUB);
    status = regexec(&pattern, "hello42world", 0, NULL, 0);
    printf("%s\n", status == 0 ? "true" : "false");
    regfree(&pattern);

    regcomp(&pattern, "([[:punct:][:space:]]+)", REG_EXTENDED);
    match = malloc(strlen(words) + 1);
    cursor = words;
    status = regexec(&pattern, cursor, 1, indices_1, 0);
    while (status == 0) {
        strcpy(match, cursor);
        match[indices_1[0].rm_so] = '\0';
        printf("%s\n", match);
        cursor += indices_1[0].rm_eo;
        status = regexec(&pattern, cursor, 1, indices_1, 0);
    }
    free(match);
    regfree(&pattern);

    free(string);
    return 0;
}
