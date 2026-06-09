#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stddef.h>

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR,
    OPEN_FILE_ERROR,
    MEMORY_ALLOCATION_ERROR
} status_code;


status_code string_to_int(const char *input_string, long *output_x);
int is_overflow(const char *str, const long converted_value);

status_code convert_to_p(const int p, const int *number, char *answer);
status_code convert_to_2(const int *number, char *answer);

int bit_add(int a, int b);
int bit_sub(int a, int b);
status_code remove_leading_zeros(char *str);
void int_to_binary(int num, char *bin);

#endif