#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "flags.h"


int is_overflow(const char *str, const long long converted_value) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%lld", converted_value);
    
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


int divisible_by_3(const char *number) {
    int sum = 0;
    for (int i = 0; number[i] != '\0'; i++) {
        sum += number[i] - '0';
    }
    return (sum % 3 == 0);
}

int divisible_by_4(const char *number) {
    int len = strlen(number);
    if (len == 1) {
        int num = number[0] - '0';
        return (num % 4 == 0);
    } else {
        int last_two = (number[len-2] - '0') * 10 + (number[len-1] - '0');
        return (last_two % 4 == 0);
    }
}

int sum_of_digits_divisible_by_9(const char *number) {
    int sum = 0;
    for (int i = 0; number[i] != '\0'; i++) {
        sum += number[i] - '0';
    }
    return (sum % 9 == 0);
}

int last_two_digits_divisible_by_25(const char *number) {
    int len = strlen(number);
    if (len == 1) {
        int num = number[0] - '0';
        return (num % 25 == 0); 
    } else {
        int last_two = (number[len-2] - '0') * 10 + (number[len-1] - '0');
        return (last_two == 0 || last_two == 25 || last_two == 50 || last_two == 75);
    }
}

int compare_strings(const char* num1, const char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    
    return strcmp(num1, num2);
}


status_code m_is_multiples(const char *dividend, const char *divisor, char *answer) {
    if (strcmp(divisor, "0") == 0) {
        *answer = 'z';
        return INPUT_ERROR;
    }
    
    if (compare_strings(dividend, divisor) < 0) {
        *answer = 'f';
        return INPUT_ERROR;
    }
    
    if (strcmp(dividend, divisor) == 0) {
        *answer = '1';
        return OK;
    }

    long long s1, s2;
    status_code convert_return1 = string_to_int(dividend, &s1);
    status_code convert_return2 = string_to_int(divisor, &s2);

    if (convert_return1 == OK && convert_return2 == OK) {
        *answer = (s1 % s2 == 0 ? '1' : '0');
        return OK;
    }
    
    if (strlen(divisor) <= 2) {
        int small_divisor = atoi(divisor);
        
        switch (small_divisor) {
            case 1:
                *answer = '1';
                return OK;
                
            case 2:
                *answer = ((dividend[strlen(dividend)-1] - '0') % 2 == 0) ? '1' : '0';
                return OK;
                
            case 3:
                *answer = divisible_by_3(dividend) ? '1' : '0';
                return OK;
                
            case 4:
                *answer = divisible_by_4(dividend) ? '1' : '0';
                return OK;
                
            case 5:
                char last_digit = dividend[strlen(dividend)-1];
                *answer = (last_digit == '0' || last_digit == '5') ? '1' : '0';
                return OK;
                
            case 6:
                if ((dividend[strlen(dividend)-1] - '0') % 2 == 0 && divisible_by_3(dividend)) {
                    *answer = '1';
                } else {
                    *answer = '0';
                }
                return OK;
            
            case 9:
                *answer = sum_of_digits_divisible_by_9(dividend) ? '1' : '0';
                return OK;

            case 10:
                *answer = (dividend[strlen(dividend)-1] == '0') ? '1' : '0';
                return OK;

            case 25:
                *answer = last_two_digits_divisible_by_25(dividend) ? '1' : '0';
                return OK;
                                
            default:
                break;
        }
    }
    
    return OVERFLOW_ERROR;
}

int double_equals(double a, double b, double epsilon) {
    return fabs(a - b) <= epsilon;
}

solution_result roots_of_equation(double epsilon, double a, double b, double c) {
    solution_result result;
    
    if (double_equals(a, 0.0, epsilon)) {
        if (double_equals(b, 0.0, epsilon)) {
            if (double_equals(c, 0.0, epsilon)) {
                sprintf(result.solutions, "a = %.3f b = %.3f c = %.3f: бесконечное множество решений", a, b, c);
            } else {
                sprintf(result.solutions, "a = %.3f b = %.3f c = %.3f: нет решений", a, b, c);
            }
        } else {
            double x = -c / b;
            sprintf(result.solutions, "a = %.3f b = %.3f c = %.3f: x = %.6f", a, b, c, x);
        }
    } else {
        double discriminant = b * b - 4 * a * c;
        
        if (double_equals(discriminant, 0.0, epsilon)) {
            double x = -b / (2 * a);
            sprintf(result.solutions, "a = %.3f b = %.3f c = %.3f: x = %.6f (кратный)", a, b, c, x);
        } else if (discriminant < -epsilon) {
            sprintf(result.solutions, "a = %.3f b = %.3f c = %.3f: нет действительных решений", a, b, c);
        } else {
            double x1 = (-b + sqrt(discriminant)) / (2 * a);
            double x2 = (-b - sqrt(discriminant)) / (2 * a);
            sprintf(result.solutions, "a = %.3f b = %.3f c = %.3f: x₁ = %.6f, x₂ = %.6f", a, b, c, x1, x2);
        }
    }
    
    return result;
}


status_code q_equation(double epsilon, double a, double b, double c, solution_result results[6]) {
    double coefficients[3] = {a, b, c};
    
    results[0] = roots_of_equation(epsilon, a, b, c); 
    results[1] = roots_of_equation(epsilon, a, c, b); 
    results[2] = roots_of_equation(epsilon, b, a, c); 
    results[3] = roots_of_equation(epsilon, b, c, a); 
    results[4] = roots_of_equation(epsilon, c, a, b); 
    results[5] = roots_of_equation(epsilon, c, b, a);     
    return OK;
}

status_code t_side_of_triangle(double epsilon, double a, double b, double c, int *is_right_triangle) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return INPUT_ERROR;
    }
    
    double sides[3] = {a, b, c};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (sides[j] > sides[j + 1]) {
                double temp = sides[j];
                sides[j] = sides[j + 1];
                sides[j + 1] = temp;
            }
        }
    }
    
    if (sides[0] + sides[1] <= sides[2]) {
        return INPUT_ERROR;
    }
    
    double leg1_sq = sides[0] * sides[0];
    double leg2_sq = sides[1] * sides[1];
    double hypotenuse_sq = sides[2] * sides[2];
    
    *is_right_triangle = fabs(leg1_sq + leg2_sq - hypotenuse_sq) < epsilon;
    return OK;
}