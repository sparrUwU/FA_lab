#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "overprintf.h"

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

int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = voverfprintf(stream, format, args);
    va_end(args);
    return result;
}

int oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = voversprintf(str, format, args);
    va_end(args);
    return result;
}

int voverfprintf(FILE *stream, const char *format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    
    const char *p = format;
    int written = 0;

    while (*p) {
        if (*p == '%') {
            p++;
            
            if (*p == 'R' && *(p+1) == 'o') {
                int value = va_arg(args, int);
                written += roman(stream, value);
                p += 2;
            }
            else if (*p == 'Z' && *(p+1) == 'r') {
                unsigned int value = va_arg(args, unsigned int);
                written += zeckendorf(stream, value);
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'v') {
                int value = va_arg(args, int);
                int base = va_arg(args, int);
                written += base_lower(stream, value, base);
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'V') {
                int value = va_arg(args, int);
                int base = va_arg(args, int);
                written += base_upper(stream, value, base);
                p += 2;
            }
            else if (*p == 't' && *(p+1) == 'o') {
                const char *str = va_arg(args, const char *);
                int base = va_arg(args, int);
                written += from_base_lower(stream, str, base);
                p += 2;
            }
            else if (*p == 'T' && *(p+1) == 'O') {
                const char *str = va_arg(args, const char *);
                int base = va_arg(args, int);
                written += from_base_upper(stream, str, base);
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'i') {
                int value = va_arg(args, int);
                written += memory_dump_int_file(stream, value);
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'u') {
                unsigned int value = va_arg(args, unsigned int);
                written += memory_dump_uint_file(stream, value);
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'f') {
                double value = va_arg(args, double);
                written += memory_dump_float_file(stream, (float)value);
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'd') {
                double value = va_arg(args, double);
                written += memory_dump_double_file(stream, value);
                p += 2;
            }
            else {
                char standard_format[3] = { '%', *p, '\0' };
                written += vfprintf(stream, standard_format, args);
                p++;
            }
        } 
        else {
            fputc(*p, stream);
            written++;
            p++;
        }
    }
    
    va_end(args_copy);
    return written;
}

int voversprintf(char *str, const char *format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    
    const char *p = format;
    int chars_written = 0;
    
    while (*p) {
        if (*p == '%') {
            p++;
            
            if (*p == 'R' && *(p+1) == 'o') {
                int value = va_arg(args, int);
                char buffer[16];
                int len = value_to_roman(value, buffer);
                strcpy(str + chars_written, buffer);
                chars_written += len;
                p += 2;
            }
            else if (*p == 'Z' && *(p+1) == 'r') {
                unsigned int value = va_arg(args, unsigned int);
                char buffer[49];
                int len = value_to_zeckendorf(value, buffer);
                strcpy(str + chars_written, buffer);
                chars_written += len;
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'v') {
                int value = va_arg(args, int);
                int base = va_arg(args, int);
                char buffer[49];
                int len = value_to_base(value, base, buffer, 0);
                strcpy(str + chars_written, buffer);
                chars_written += len;
                p += 2;
            }
            else if (*p == 'C' && *(p+1) == 'V') {
                int value = va_arg(args, int);
                int base = va_arg(args, int);
                char buffer[49];
                int len = value_to_base(value, base, buffer, 1);
                strcpy(str + chars_written, buffer);
                chars_written += len;
                p += 2;
            }
            else if (*p == 't' && *(p+1) == 'o') {
                const char *input_str = va_arg(args, const char *);
                int base = va_arg(args, int);
                char buffer[32];
                int len = from_base_to_string(input_str, base, 0, buffer, sizeof(buffer));
                strcpy(str + chars_written, buffer);
                chars_written += len;
                p += 2;
            }
            else if (*p == 'T' && *(p+1) == 'O') {
                const char *input_str = va_arg(args, const char *);
                int base = va_arg(args, int);
                char buffer[32];
                int len = from_base_to_string(input_str, base, 1, buffer, sizeof(buffer));
                strcpy(str + chars_written, buffer);
                chars_written += len;
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'i') {
                int value = va_arg(args, int);
                int len = memory_dump_int_string(str + chars_written, INT_MAX, value);
                if (len > 0) chars_written += len;
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'u') {
                unsigned int value = va_arg(args, unsigned int);
                int len = memory_dump_uint_string(str + chars_written, INT_MAX, value);
                if (len > 0) chars_written += len;
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'f') {
                double value = va_arg(args, double);
                int len = memory_dump_float_string(str + chars_written, INT_MAX, (float)value);
                if (len > 0) chars_written += len;
                p += 2;
            }
            else if (*p == 'm' && *(p+1) == 'd') {
                double value = va_arg(args, double);
                int len = memory_dump_double_string(str + chars_written, INT_MAX, value);
                if (len > 0) chars_written += len;
                p += 2;
            }
            else {
                char spec[3] = { '%', *p, '\0' };
                int len = vsprintf(str + chars_written, spec, args_copy);
                if (len > 0) chars_written += len;
                p++;
            }
        } 
        else {
            str[chars_written++] = *p++;
        }
    }
    
    str[chars_written] = '\0';
    va_end(args_copy);
    return chars_written;
}

int value_to_roman(int value, char *buffer) {
    if (value < 1 || value > 3999) {
        buffer[0] = '\0';
        return 0;
    }
    
    int written = 0;
    
    for (int i = 0; i < roman_table_size; i++) {
        while (value >= roman_numerals[i].value) {
            const char *numeral = roman_numerals[i].numeral;
            while (*numeral != '\0') {
                buffer[written++] = *numeral++;
            }
            value -= roman_numerals[i].value;
        }
    }
    
    buffer[written] = '\0';
    return written;
}

int roman(FILE *stream, int value) {
    char buffer[16];
    int len = value_to_roman(value, buffer);
    return fwrite(buffer, 1, len, stream);
}

int value_to_zeckendorf(unsigned int value, char *buffer) {
    if (value == 0) {
        strcpy(buffer, "1");
        return 1;
    }
    
    unsigned int fib[48];
    fib[0] = 1;
    fib[1] = 2;
    int count = 2;
    
    while (fib[count-1] <= value) {
        fib[count] = fib[count-1] + fib[count-2];
        count++;
    }
    
    int written = 0;
    unsigned int temp = value;
    
    for (int i = count - 1; i >= 0; i--) {
        if (temp >= fib[i]) {
            buffer[written++] = '1';
            temp -= fib[i];
            i--;
        } else {
            buffer[written++] = '0';
        }
    }
    
    buffer[written++] = '1';
    buffer[written] = '\0';
    
    return written;
}

int zeckendorf(FILE *stream, unsigned int value) {
    char buffer[49];
    int len = value_to_zeckendorf(value, buffer);
    return fwrite(buffer, 1, len, stream);
}

int value_to_base(int value, int base, char *buffer, int uppercase) {
    if (base < 2 || base > 36) {
        base = 10;
    }

    if (value == 0) {
        strcpy(buffer, "0");
        return 1;
    }
    
    int index = 0;
    unsigned int num;
    int is_negative = 0;
    
    if (base == 10 && value < 0) {
        is_negative = 1;
        num = (unsigned int)(-value);
    } else {
        num = (unsigned int)value;
    }
    
    char temp_buffer[34];
    int temp_index = 0;
    
    do {
        unsigned int digit = num % base;
        if (digit < 10) {
            temp_buffer[temp_index++] = '0' + digit;
        } else {
            char letter_base = uppercase ? 'A' : 'a';
            temp_buffer[temp_index++] = letter_base + (digit - 10);
        }
        num /= base;
    } while (num > 0 && temp_index < 33);
    
    if (is_negative) {
        buffer[index++] = '-';
    }
    
    for (int i = temp_index - 1; i >= 0; i--) {
        buffer[index++] = temp_buffer[i];
    }
    
    buffer[index] = '\0';
    return index;
}

int base_lower(FILE *stream, int value, int base) {
    char buffer[34];
    int len = value_to_base(value, base, buffer, 0);
    return fwrite(buffer, 1, len, stream);
}

int base_upper(FILE *stream, int value, int base) {
    char buffer[34];
    int len = value_to_base(value, base, buffer, 1);
    return fwrite(buffer, 1, len, stream);
}

int value_from_base(const char *str, int base, int uppercase) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    
    int result = 0;
    int is_negative = 0;
    int i = 0;
    
    while ((unsigned char)str[i] == ' ') {
        i++;
    }
    
    if (str[i] == '-') {
        is_negative = 1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    while (str[i] != '\0') {
        char c = str[i];
        int digit;
        
        if (isdigit((unsigned char)c)) {
            digit = c - '0';
        } else if (isalpha((unsigned char)c)) {
            if (uppercase) {
                if (c >= 'A' && c <= 'Z') {
                    digit = c - 'A' + 10;
                } else {
                    break;
                }
            } else {
                if (c >= 'a' && c <= 'z') {
                    digit = c - 'a' + 10;
                } else {
                    break;
                }
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
    
    return is_negative ? -result : result;
}

int from_base_to_string(const char *str, int base, int uppercase, char *buffer, int buffer_size) {
    int value = value_from_base(str, base, uppercase);
    return snprintf(buffer, buffer_size, "%d", value);
}

int from_base_lower(FILE *stream, const char *str, int base) {
    int value = value_from_base(str, base, 0);
    return fprintf(stream, "%d", value);
}

int from_base_upper(FILE *stream, const char *str, int base) {
    int value = value_from_base(str, base, 1);
    return fprintf(stream, "%d", value);
}

int memory_dump_to_string(char *str, int str_size, const void *value, size_t size) {
    const unsigned char *bytes = (const unsigned char *)value;
    int chars_written = 0;
    
    for (size_t i = 0; i < size; i++) {
        unsigned char byte = bytes[i];
        
        for (int j = 7; j >= 0; j--) {
            if (chars_written < str_size - 1) {
                str[chars_written++] = (byte & (1 << j)) ? '1' : '0';
            }
        }
        
        if (i < size - 1 && chars_written < str_size - 1) {
            str[chars_written++] = ' ';
        }
    }
    
    str[chars_written] = '\0';
    return chars_written;
}

int memory_dump_int_string(char *str, int str_size, int value) {
    return memory_dump_to_string(str, str_size, &value, sizeof(int));
}

int memory_dump_uint_string(char *str, int str_size, unsigned int value) {
    return memory_dump_to_string(str, str_size, &value, sizeof(unsigned int));
}

int memory_dump_double_string(char *str, int str_size, double value) {
    return memory_dump_to_string(str, str_size, &value, sizeof(double));
}

int memory_dump_float_string(char *str, int str_size, float value) {
    return memory_dump_to_string(str, str_size, &value, sizeof(float));
}

int memory_dump_int_file(FILE *stream, int value) {
    char buffer[36];
    int len = memory_dump_int_string(buffer, sizeof(buffer), value);
    return fwrite(buffer, 1, len, stream);
}

int memory_dump_uint_file(FILE *stream, unsigned int value) {
    char buffer[36];
    int len = memory_dump_uint_string(buffer, sizeof(buffer), value);
    return fwrite(buffer, 1, len, stream);
}

int memory_dump_float_file(FILE *stream, float value) {
    char buffer[36];
    int len = memory_dump_float_string(buffer, sizeof(buffer), value);
    return fwrite(buffer, 1, len, stream);
}

int memory_dump_double_file(FILE *stream, double value) {
    char buffer[72];
    int len = memory_dump_double_string(buffer, sizeof(buffer), value);
    return fwrite(buffer, 1, len, stream);
}