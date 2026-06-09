#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

status_code string_to_int(const char *input_string, long *output_x) {  
    if (input_string == NULL) {
        return INPUT_ERROR;
    }

    char *endptr;
    while (*input_string == ' ' || *input_string == '\t') {
        ++input_string;
    }
    
    long convert_result = strtol(input_string, &endptr, 10);
        
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

int is_overflow(const char *str, const long converted_value) {
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

status_code convert_to_p(const int p, const int *number, char *answer) {
    if (!number || !answer) return INPUT_ERROR;

    int r = 0;

    if (p == 2) {
        status_code status = convert_to_2(number, answer);
        return status;
    }

    else if (p == 4) r = 2;
    else if (p == 8) r = 3;
    else if (p == 16) r = 4;
    else if (p == 32) r = 5;
    else return INPUT_ERROR;

    char bin[33];
    int_to_binary(*number, bin);

    int i = 31;
    int idx = 0;
    int bit_cnt = 0;
    int out = 0;

    while (i >= 0) {
        int bit = bin[bit_sub(31, i)] & 1;

        out |= (bit << (bit_sub(r, bit_add(bit_cnt, 1))));
        bit_cnt = bit_add(bit_cnt, 1);

        if (bit_cnt == r) {
            char c;

            if (out < 10)
                c = bit_add('0', out);
            else
                c = bit_add('A', bit_sub(out, 10));

            answer[idx] = c;
            idx = bit_add(idx, 1); //4294967300

            out = 0;
            bit_cnt = 0;
        }

        i = bit_sub(i, 1);
    }

    answer[idx] = '\0';
    remove_leading_zeros(answer);

    return OK;
}

status_code convert_to_2(const int *number, char *answer) {
    if (!number || !answer) return INPUT_ERROR;

    int i = 31;
    int pos = 0;

    while (i >= 0) {
        answer[pos] = (( (*number >> i) & 1 ) | '0');
        pos = bit_add(pos, 1);
        i = bit_sub(i, 1);
    }

    answer[pos] = '\0';

    remove_leading_zeros(answer);
    return OK;
}

int bit_add(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

int bit_sub(int a, int b) {
    while (b != 0) {
        int borrow = (~a & b) << 1;
        a = a ^ b;
        b = borrow;
    }
    return a;
}

void int_to_binary(int num, char *bin) {
    int i = 31;
    int pos = 0;

    while (i >= 0) {
        bin[pos] = ((num >> i) & 1) | '0';
        pos = bit_add(pos, 1);
        i = bit_sub(i, 1);
    }
    bin[32] = '\0';
}

status_code remove_leading_zeros(char *str) {
    int len = strlen(str);
    int i = 0;

    while (i < bit_sub(len, 1) && str[i] == '0') {
        i = bit_add(i, 1);
    }

    if (i > 0) {
        memmove(str, str + i, bit_add(len, 1) - i);
    }
    return OK;
}