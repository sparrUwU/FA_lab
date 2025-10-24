#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR,
    FILE_ERROR,
} status_code;

void to_upper(char *str);

int find_minimal_base(const char *str, status_code *status);

status_code process_file(FILE *input, FILE *output);

status_code remove_leading_zeros(char *str);

#endif