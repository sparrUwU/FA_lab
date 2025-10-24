#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

int is_latin_letter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int is_arabic_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

status_code d_delete_numbers(FILE *input, FILE *output) {
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!is_arabic_digit(ch)) {
            fputc(ch, output);
        }
    }
    return OK;
}

status_code i_count_latin(FILE *input, FILE *output) {
    int ch;
    int count = 0;
    int line_has_content = 0;

    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') {
            fprintf(output, "%d\n", count);
            count = 0;
            line_has_content = 0;
        } else {
            line_has_content = 1;
            if (is_latin_letter(ch)) {
                count++;
            }
        }
    }

    if (line_has_content) {
        fprintf(output, "%d\n", count);
    }

    return OK;
}

status_code s_count_special(FILE *input, FILE *output) {
    int ch;
    int count = 0;
    int line_has_content = 0;

    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') {
            fprintf(output, "%d\n", count);
            count = 0;
            line_has_content = 0;
        } else {
            line_has_content = 1;
            if (!is_latin_letter(ch) && !is_arabic_digit(ch) && ch != ' ' && ch != '\t' && ch != '\r') {
                count++;
            }
        }
    }

    if (line_has_content) {
        fprintf(output, "%d\n", count);
    }

    return OK;
}

status_code a_to_ascii(FILE *input, FILE *output) {
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (is_arabic_digit(ch)) {
            fputc(ch, output);
        } else {
            fprintf(output, "%02X", (unsigned char)ch);
        }
    }
    return OK;
}