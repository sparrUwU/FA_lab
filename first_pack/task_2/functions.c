#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"


long Er_prime(long number)
{
    static long *mass = NULL;
    static long primes_count = 0;
    if (number == 0) {
        long n = 1000000 * 20;
        bool *is_prime = (bool*)malloc((n + 1) * sizeof(bool));
        
        for (long i = 0; i <= n; i++)
            is_prime[i] = true;
        is_prime[0] = is_prime[1] = false;

        long p;
        for (long i = 0; i < n; i++)
            mass[i] = i + 2;
        for (long i = 2; i * i < n; i++) {
            if (is_prime[i]) {
                for (long j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        
        primes_count = 0;
        for (long i = 2; i <= n; i++) {
            if (is_prime[i]) {
                primes_count++;
            }
        }
        
        if (mass != NULL) free(mass);
        mass = (long *)malloc(primes_count * sizeof(long));
        long idx = 0;
        for (long i = 2; i <= n; i++) {
            if (is_prime[i]) {
                mass[idx++] = i;
            }
        }
        
        free(is_prime);
        return OK;

    } else if (number == -1) {
        if (mass != NULL) {
            free(mass);
            mass = NULL;
        }
        return OK;
    }

    if (number > primes_count) {
        return -1;
    }

    return mass[number - 1];
}


int is_overflow(const char *str, const long converted_value) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%ld", converted_value);
    
    const char *original_str = str;
    const char *buf_str = buffer;

    while (*original_str == ' ' || *original_str == '\t') original_str++;
        
    if (*original_str == '-' || *original_str == '+') original_str++;
    if (*buf_str == '-') buf_str++;
    
    while (*original_str == '0') original_str++;
    while (*buf_str == '0') buf_str++;
    
    return (strcmp(original_str, buf_str) != 0);
}


status_code string_to_int(const char *input_string, long *output_x) {  
    if (input_string == NULL) {
        return INPUT_ERROR;
    }

    char *endptr;
    const long convert_result = strtol(input_string, &endptr, 10);
        
    if (endptr == input_string) {
        return INPUT_ERROR;
    }
    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
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