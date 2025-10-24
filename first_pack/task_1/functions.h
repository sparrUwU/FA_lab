#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR
} status_code;

int is_overflow(const char *str, const long long converted_value);

status_code string_to_int(const char *input_string, long long *output_x);

status_code h_finding_multiples(const long long *x, long long *ans_pointer);

status_code p_is_composite(const long long *x, int *ans_pointer);

status_code s_16_notation(const char *x, char *ans_pointer);

status_code e_pow_table(const long long *x, long long *ans_pointer);

status_code a_sum_to_x(const long long *x, long long *ans_pointer); 

status_code f_factorial(const long long *x, long long *ans_pointer);

#endif