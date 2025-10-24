#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR
} status_code;

int is_latin_letter(char ch);
int is_arabic_digit(char ch);

status_code d_delete_numbers(FILE *input, FILE *output);
status_code i_count_latin(FILE *input, FILE *output);
status_code s_count_special(FILE *input, FILE *output);
status_code a_to_ascii(FILE *input, FILE *output);

#endif