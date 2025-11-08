#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "overscanf.h"

typedef struct {
    int value;
    const char *numeral;
} RomanNumeral;

static const RomanNumeral roman_numerals[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"},  {90, "XC"},  {50, "L"},  {40, "XL"},
    {10, "X"},   {9, "IX"},   {5, "V"},   {4, "IV"},
    {1, "I"}
};

static const int roman_table_size = sizeof(roman_numerals) / sizeof(roman_numerals[0]);

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = voverfscanf(stream, format, args);
    va_end(args);
    return result;
}

int oversscanf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = voversscanf(str, format, args);
    va_end(args);
    return result;
}

int voverfscanf(FILE *stream, const char *format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    
    const char *p = format;
    int total_scanned = 0;
    
    while (*p) {
        if (*p == '%') {
            p++;
            
            if (*p == 'R' && *(p+1) == 'o') {
                int *value_ptr = va_arg(args, int*);
                char buffer[16];
                if (fscanf(stream, "%15s", buffer) == 1) {
                    int len;
                    int value = parse_roman(buffer, &len);
                    if (len > 0) {
                        *value_ptr = value;
                        total_scanned++;
                    }
                }
                p += 2;
            }
            else if (*p == 'Z' && *(p+1) == 'r') {
                unsigned int *value_ptr = va_arg(args, unsigned int*);
                char buffer[49];
                if (fscanf(stream, "%48s", buffer) == 1) {
                    int len;
                    unsigned int value = parse_zeckendorf(buffer, &len);
                    if (len > 0) {
                        *value_ptr = value;
                        total_scanned++;
                    }
                }
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'v') {
                int *value_ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                char buffer[49];
                if (fscanf(stream, "%48s", buffer) == 1) {
                    int len;
                    int value = parse_base(buffer, base, &len, 0);
                    if (len > 0) {
                        *value_ptr = value;
                        total_scanned++;
                    }
                }
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'V') {
                int *value_ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                char buffer[49];
                if (fscanf(stream, "%48s", buffer) == 1) {
                    int len;
                    int value = parse_base(buffer, base, &len, 1);
                    if (len > 0) {
                        *value_ptr = value;
                        total_scanned++;
                    }
                }
                p += 2;
            }
            else {
                char standard_format[3] = { '%', *p, '\0' };
                int result = vfscanf(stream, standard_format, args_copy);
                if (result == 1) {
                    total_scanned++;
                }
                p++;
            }
        } 
        else {
            p++;
        }
    }
    
    va_end(args_copy);
    return total_scanned;
}

int voversscanf(char *str, const char *format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    
    const char *p = format;
    const char *s = str;
    int total_scanned = 0;
    
    while (*p && *s) {
        if (*p == '%') {
            p++;
            
            if (*p == 'R' && *(p+1) == 'o') {
                int *value_ptr = va_arg(args, int*);
                int len;
                int value = parse_roman(s, &len);
                
                if (len > 0) {
                    *value_ptr = value;
                    total_scanned++;
                    s += len;
                }
                p += 2;
            }
            else if (*p == 'Z' && *(p+1) == 'r') {
                unsigned int *value_ptr = va_arg(args, unsigned int*);
                int len;
                unsigned int value = parse_zeckendorf(s, &len);
                
                if (len > 0) {
                    *value_ptr = value;
                    total_scanned++;
                    s += len;
                }
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'v') {
                int *value_ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                int len;
                int value = parse_base(s, base, &len, 0);
                
                if (len > 0) {
                    *value_ptr = value;
                    total_scanned++;
                    s += len;
                }
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'V') {
                int *value_ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                int len;
                int value = parse_base(s, base, &len, 1);
                
                if (len > 0) {
                    *value_ptr = value;
                    total_scanned++;
                    s += len;
                }
                p += 2;
            }
            else {
                char standard_format[3] = { '%', *p, '\0' };
                int result = vsscanf(s, standard_format, args_copy);
                
                if (result == 1) {
                    total_scanned++;
                    while (*s && !isspace(*s)) {
                        s++;
                    }
                    while (*s && isspace(*s)) {
                        s++;
                    }
                }
                p++;
            }
        } 
        else {
            p++;
            s++;
        }
    }
    
    va_end(args_copy);
    return total_scanned;
}


int parse_roman(const char *str, int *len) {
    int result = 0;
    int i = 0;
    *len = 0;
    
    for (int j = 0; j < roman_table_size; j++) {
        const char *numeral = roman_numerals[j].numeral;
        int str_len = strlen(numeral);
        
        if (strncmp(str + *len, numeral, str_len) == 0) {
            result += roman_numerals[j].value;
            *len += str_len;
        }
    }

    return result;
}

int parse_zeckendorf(const char *str, int *len) {
    *len = 0;
    
    int start_index = 0;
    while (str[start_index] == '0') {
        start_index++;
    }

    if (str[*len] == '\0') {
        return 0;
    }
    
    unsigned int fib[48];
    fib[0] = 1;
    fib[1] = 2;
    int count = 2;
    
    while (count < 48) {
        fib[count] = fib[count-1] + fib[count-2];
        count++;
    }
    
    unsigned int result = 0;
    int fib_index = start_index;
    int str_len = strlen(str);
    
    for (int i = start_index; i < str_len - 1; i++) {
        if (str[i] == '1') {
            if (fib_index < count) {
                result += fib[fib_index];
            }
        } else if (str[i] != '0') {
            break;
        }
        fib_index++;
    }
    
    if (str[str_len - 1] == '1') {
        *len = str_len;
    } else {
        *len = 0;
        result = 0;
    }
    
    return result;
}

int parse_base(const char *str, int base, int *len, int uppercase) {
    *len = 0;
    
    if (base < 2 || base > 36) {
        base = 10;
    }
    
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    while (str[i] != '\0') {
        char c = str[i];
        int digit;
        
        if (isdigit(c)) {
            digit = c - '0';
        } else if (isalpha(c)) {
            if (uppercase) {
                digit = toupper(c) - 'A' + 10;
            } else {
                digit = tolower(c) - 'a' + 10;
            }
        } else {
            break;
        }
        
        if (digit >= base) {
            break;
        }
        
        result = result * base + digit;
        i++;
    }
    
    *len = i;
    return result * sign;
}