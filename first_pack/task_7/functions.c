#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"

void to_upper(char *str) {
    if (str != NULL) {    
        for (size_t i = 0; str[i] != '\0'; i++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                str[i] = str[i] - 'a' + 'A';
            }
        }
    }
}

int find_minimal_base(const char *str, status_code *status) {
    if (str == NULL || status == NULL) {
        *status = INPUT_ERROR;
        return -1;
    }
    
    if (strlen(str) == 0) {
        *status = INPUT_ERROR;
        return -1;
    }
    
    int max_digit_value = -1;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        char c = str[i];
        int digit_value;
        
        if (c >= '0' && c <= '9') {
            digit_value = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit_value = c - 'A' + 10;
        } else {
            *status = INPUT_ERROR;
            return -1;
        }
        
        if (digit_value > max_digit_value) {
            max_digit_value = digit_value;
        }
    }
    
    if (max_digit_value == 0 && len > 0) {
        *status = OK;
        return 2;
    }
    
    int base = (max_digit_value + 1) < 2 ? 2 : (max_digit_value + 1);
    
    *status = OK;
    return base;
}

status_code remove_leading_zeros(char *str) {
    if (str == NULL) {
        return INPUT_ERROR;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return OK;
    }
    
    size_t start_index = 0;
    while (start_index < len && str[start_index] == '0') {
        start_index++;
    }
    
    if (start_index == len) {
        str[0] = '0';
        str[1] = '\0';
        return OK;
    }
    
    if (start_index > 0) {
        size_t i = 0;
        while (str[start_index + i] != '\0') {
            str[i] = str[start_index + i];
            i++;
        }
        str[i] = '\0';
    }
    
    return OK;
}

status_code process_file(FILE *input, FILE *output) {
    if (input == NULL || output == NULL) {
        return INPUT_ERROR;
    }
    
    char token[101];
    status_code result = OK;
    
    while (fscanf(input, "%100s", token) == 1) {
        char number[101];
        strcpy(number, token);
        
        to_upper(number);
        
        status_code remove_status = remove_leading_zeros(number);
        if (remove_status != OK) {
            result = remove_status;
            continue;
        }
        
        status_code base_status;
        int base = find_minimal_base(number, &base_status);
        
        if (base_status != OK || base == -1) {
            if (result == OK) {
                result = base_status;
            }
            continue;
        }
        
        char *end_ptr;
        long long decimal_value = strtoll(number, &end_ptr, base);
        
        if (end_ptr == number || *end_ptr != '\0') {
            if (result == OK) {
                result = INPUT_ERROR;
            }
            continue;
        }
        
        if (fprintf(output, "%s %d %lld\n", number, base, decimal_value) < 0) {
            result = FILE_ERROR;
            break;
        }
    }
    
    if (ferror(input)) {
        return FILE_ERROR;
    }
    
    return result;
}