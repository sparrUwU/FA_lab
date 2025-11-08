#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


status_code remove_insignificant_zeros(char *str) {
    if (str == NULL || *str == '\0') {
        return MEMORY_ALLOCATION_ERROR;
    }
    
    char* decimalPoint = strchr(str, '.');
    if (decimalPoint == NULL) {
        return INPUT_ERROR;
    }
    
    char* end = str + strlen(str) - 1;
    
    while (end > decimalPoint && *end == '0') {
        *end = '\0';
        end--;
    }
    
    if (end == decimalPoint) {
        *(end + 1) = '0';
        *(end + 2) = '\0';
    }

    return OK;
}


int is_pow_2_or_5(const char *notation) {
    char *result = malloc(strlen(notation) + 1);
    char *previous_result = malloc(strlen(notation) + 1);
    strcpy(previous_result, notation);
    bool flag_5 = 0;

    while (string_dividing_2_or_5(previous_result, "5", result) == 0) {
        if (!strcmp(result, "1")) {
            free(result);
            free(previous_result);
            return 5;
        }

        flag_5 = 1;
        strcpy(previous_result, result);
        strcpy(result, "1");
    }

    while (string_dividing_2_or_5(previous_result, "2", result) == 0) {
        if (!strcmp(result, "1")) {
            free(result);
            free(previous_result);
            if (flag_5) {
                return 10;
            }

            return 2;
        }

        strcpy(previous_result, result);
        strcpy(result, "1");
    }

    free(result);
    free(previous_result);
    return 0;
}


bool string_dividing_2_or_5(const char *numerator, const char *denominator, char *result) {
    int divisor = (denominator[0] == '2') ? 2 : 5;
    int len = strlen(numerator);
    
    char *temp_result = malloc(len + 1);
    if (temp_result == NULL) {
        return 1;
    }
    
    int carry = 0;
    int result_idx = 0;
    int has_non_zero = 0;
    
    for (int i = 0; i < len; i++) {
        int current_digit = numerator[i] - '0';
        int number = carry * 10 + current_digit;
        
        int quotient_digit = number / divisor;
        carry = number % divisor;
        
        if (quotient_digit != 0 || has_non_zero) {
            temp_result[result_idx++] = quotient_digit + '0';
            has_non_zero = 1;
        }
    }
        
    temp_result[result_idx] = '\0';
    strcpy(result, temp_result);
    free(temp_result);
    
    return (carry != 0);
}


status_code is_everlasting(char *notation, bool *answer, int n, ...) {
    if (notation == NULL || answer == NULL) {
        return INPUT_ERROR;
    }
    
    int is_pow = is_pow_2_or_5(notation);
    
    va_list number;
    va_start(number, n);


    if (is_pow == 0) {
        for (int i = 0; i < n; ++i) {
            char *current = va_arg(number, char*);
            if (current == NULL) {
                answer[i] = true;
                continue;
            }
            
            char *copy = malloc(strlen(current) + 1);
            if (copy == NULL) {
                answer[i] = true;
                continue;
            }
            strcpy(copy, current);
            
            if (remove_insignificant_zeros(copy) != OK) {
                answer[i] = true;
            } else {
                answer[i] = (strcmp(copy, "0.0") != 0);
            }
            free(copy);
        }
    }

    else if (is_pow == 10) {
        for (int i = 0; i < n; ++i) {
            answer[i] = false;
            va_arg(number, char*);
        }
    }

else if (is_pow == 5 || is_pow == 2) {
        for (int i = 0; i < n; ++i) {
            char *current = va_arg(number, char*);
            if (current == NULL) {
                answer[i] = true;
                continue;
            }
            
            char *copy = malloc(strlen(current) + 1);
            if (copy == NULL) {
                answer[i] = true;
                continue;
            }
            strcpy(copy, current);
            
            if (remove_insignificant_zeros(copy) != OK) {
                answer[i] = true;
                free(copy);
                continue;
            }
            
            if (strcmp(copy, "0.0") == 0) {
                answer[i] = false;
                free(copy);
                continue;
            }

            char *decimal_point = strchr(copy, '.');
            if (decimal_point == NULL) {
                answer[i] = true;
                free(copy);
                continue;
            }
            
            char *fractional_part = decimal_point + 1;
            if (strlen(fractional_part) == 0) {
                answer[i] = true;
                free(copy);
                continue;
            }

            char *numerator = malloc(strlen(fractional_part) + 1);
            char *result = malloc(strlen(fractional_part) + 1);
            
            if (numerator == NULL || result == NULL) {
                free(numerator);
                free(result);
                answer[i] = true;
                free(copy);
                continue;
            }
            
            strcpy(numerator, fractional_part);
            const char *divisor = (is_pow == 5) ? "2" : "5";
            
            char *temp_num = malloc(strlen(numerator) + 1);
            if (temp_num == NULL) {
                free(numerator);
                free(result);
                answer[i] = false;
                free(copy);
                continue;
            }
            
            strcpy(temp_num, numerator);
            
            bool ans = false;
            int to_div = strlen(numerator);
            while (strcmp(temp_num, "1") != 0 && to_div != 0) {
                if (string_dividing_2_or_5(temp_num, divisor, result)) {
                    ans = true;
                    break;
                }
                --to_div;
                strcpy(temp_num, result);
            }
            
            answer[i] = ans;
            
            free(numerator);
            free(result);
            free(temp_num);
            free(copy);
        }
    }

    va_end(number);
    return OK;
}