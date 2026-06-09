#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include "functions.h"


int is_overflow(const char *str, const long long converted_value) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%ld", converted_value); 
    
    const char *original_str = str;
    const char *buf_str = buffer;

    while (*original_str == ' ' || *original_str == '\t') ++original_str;
        
    if (*original_str == '-' || *original_str == '+') ++original_str;
    if (*buf_str == '-') ++buf_str;
     
    while (*original_str == '0') ++original_str;
    while (*buf_str == '0') ++buf_str;
    
    return (strcmp(original_str, buf_str) != 0);
}

status_code string_to_int(const char *input_string, long long *output_x) {  
    if (input_string == NULL) {
        return INPUT_ERROR;
    }

    char *endptr;
    while (*input_string == ' ' || *input_string == '\t') {
        ++input_string;
    }
    
    long long convert_result = strtoll(input_string, &endptr, 10);
        
    if (endptr == input_string) {
        return INPUT_ERROR;
    }
    while (*endptr == ' ' || *endptr == '\t') {
        ++endptr;
    }

    if (*endptr != '\0') {
        return INPUT_ERROR;
    }

    if (is_overflow(input_string, convert_result)) {
        return OVERFLOW_ERROR;
    }
    
    *output_x = convert_result;
    return OK;
}

status_code h_finding_multiples(const long long *x, long long *ans_pointer) {
    if (*x > 100) {
        *ans_pointer = 0;
        return OK;
    }

    if (*x <= 0) {
        return INPUT_ERROR;
    }

    for (long long i = *x; i <= 100; i += *x) {
        *ans_pointer = i;
        ans_pointer++;
    }

    *ans_pointer = 0;

    return OK;
}

status_code p_is_composite(const long long *x, int *ans_pointer) {
    if (*x <= 1) {
        return INPUT_ERROR;
    }

    if (*x == 2) {
        *ans_pointer = 0;
        return OK;
    }

    if (*x % 2 == 0) {
        *ans_pointer = 1;
        return OK;
    }

    for (long long i = 3; i * i <= *x; i += 2) {
        if (*x % i == 0) {
            *ans_pointer = 1;
            return OK;
        }
    }

    *ans_pointer = 0;
    return OK;
}

status_code s_16_notation(const char *decimal_number, char *result) {
    if (decimal_number == NULL || strlen(decimal_number) == 0) {
        return INPUT_ERROR;
    }
    
    for (int i = 0; decimal_number[i] != '\0'; i++) {
        if (!isdigit(decimal_number[i])) {
            return INPUT_ERROR;
        }
    }

    if (strcmp(decimal_number, "0") == 0) {
        strcpy(result, "0");
        return OK;
    }
    
    int len = strlen(decimal_number);
    char *temp = (char*)malloc(len + 1);
    if (temp == NULL) {
        return OVERFLOW_ERROR;
    }
    strcpy(temp, decimal_number);
    
    int result_index = 0;
    char hex_digits[] = "0123456789ABCDEF";
    
    while (strcmp(temp, "0") != 0) {
        int remainder = 0;
        
        for (int i = 0; temp[i] != '\0'; i++) {
            int current = remainder * 10 + (temp[i] - '0');
            temp[i] = (current / 16) + '0';
            remainder = current % 16;
        }
        
        char *clean = temp;
        while (*clean == '0' && *(clean + 1) != '\0') {
            clean++;
        }

        if (clean != temp) {
            strcpy(temp, clean);
        }
        
        result[result_index++] = hex_digits[remainder];
    }
    
    for (int i = 0; i < result_index / 2; i++) {
        char temp_char = result[i];
        result[i] = result[result_index - 1 - i];
        result[result_index - 1 - i] = temp_char;
    }
    
    result[result_index] = '\0';
    free(temp);
    
    return OK;
}


status_code e_pow_table(const long long *max_power, long long *results) {
    if (*max_power < 1 || *max_power > 10) {
        return INPUT_ERROR;
    }

    int result_index = 0;
    for (long long base = 1; base <= 10; base++) {
        long long current_power = 1;
        
        for (long long power = 1; power <= *max_power; power++) {
            current_power *= base;
            results[result_index++] = current_power;
        }
    }
    
    return OK;
}
 
status_code a_sum_to_x(const long long *x, long long *result) {
    if (*x <= 0) {
        return INPUT_ERROR;
    }
    
    long long temp = *x + 1;
    
    if (*x % 2 == 0) {
        if (*x / 2 > LLONG_MAX / temp) {
            return OVERFLOW_ERROR;
        }
        *result = (*x / 2) * temp;
    } else {
        if (*x > LLONG_MAX / (temp / 2)) {
            return OVERFLOW_ERROR;
        }
        *result = *x * (temp / 2);
    }
    
    return OK;
}

status_code f_factorial(const long long *x, long long *ans_pointer) {
    if (*x < 0) {
        return INPUT_ERROR;
    }
    
    if (*x > 20) {
        return OVERFLOW_ERROR;
    }

    *ans_pointer = 1;
    for (long long i = 2; i <= *x; ++i) {
        *ans_pointer *= i;
    }

    return OK;
}