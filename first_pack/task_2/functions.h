#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR
} status_code;

int is_overflow(const char *str, const long converted_value);

status_code string_to_int(const char *input_string, long *output_x);

long Er_prime(int number);

#endif