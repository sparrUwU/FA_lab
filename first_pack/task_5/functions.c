#include <stdio.h>
#include <functions.h>
#include <ctype.h>


status_code d_delete_numbers(FILE *input, FILE *output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, output);
        }
    }
};

status_code i_count_latin(FILE *input, FILE *output) {
    char ch, prev;
    int count = 0;
    int str_num = 1;

    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') {
            fprintf(output, "%d: %d\n", str_num, count);
            ++str_num;
            count = 0;
        } else if (isalpha(ch)) {
            ++count;
        }
        prev = ch;
    }

    if (prev != '\n') {
        fprintf(output, "%d: %d\n", str_num, count);
    }

    return OK;
};

status_code s_count_special(FILE *input, FILE *output) {
    char ch, prev;
    int count = 0;
    int str_num = 1;

    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') {
            ++count;
            fprintf(output, "%d: %d\n", str_num, count);
            ++str_num;
            count = 0;
        } else if (!is_latin_letter(ch) && !is_arabic_digit(ch) && ch != ' ') {
            ++count;
        }
        prev = ch;
    }

    if (prev != '\n') {
        fprintf(output, "%d: %d\n", str_num, count);
    }

    return OK;
};

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
};