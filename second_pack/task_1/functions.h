#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR,
    MEMORY_ALLOCATION_ERROR
} status_code;

bool string_dividing_2_or_5(const char *numerator, const char *denominator, char *result);
int is_pow_2_or_5(const char *notation);
status_code remove_insignificant_zeros(char *str);
status_code is_everlasting(char *notation, bool *answer, int n, ...);

#endif