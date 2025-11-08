#include <stdio.h>
#include <stdarg.h>
#include "functions.h"

void print_results(const char* notation, bool* answers, int count, ...) {
    printf("Основание системы счисления: %s\n", notation);
    printf("Проверка дробей на бесконечное представление:\n");
    
    va_list fractions;
    va_start(fractions, count);
    
    for (int i = 0; i < count; i++) {
        char* fraction = va_arg(fractions, char*);
        printf("  %-15s -> %s\n", fraction, answers[i] ? "БЕСКОНЕЧНОЕ" : "КОНЕЧНОЕ");
    }
    
    va_end(fractions);
    printf("\n");
}

int main() {
    bool answers1[4];
    is_everlasting("10", answers1, 4, "0.5", "0.25", "0.3333333333", "0.75");
    print_results("10", answers1, 4, "0.5", "0.25", "0.3333333333", "0.75");
    
    bool answers2[5];
    is_everlasting("2", answers2, 5, "0.5", "0.25", "0.3333333333", "0.1", "0.75");
    print_results("2", answers2, 5, "0.5", "0.25", "0.3333333333", "0.1", "0.75");
    
    bool answers3[4];
    is_everlasting("5", answers3, 4, "0.2", "0.04", "0.3333333333", "0.1");
    print_results("5", answers3, 4, "0.2", "0.04", "0.3333333333", "0.1");
    
    bool answers4[3];
    is_everlasting("8", answers4, 3, "0.125", "0.3333333333", "0.5");
    print_results("8", answers4, 3, "0.125", "0.3333333333", "0.5");
    
    bool answers5[3];
    is_everlasting("3", answers5, 3, "0.1", "0.2", "0.5");
    print_results("3", answers5, 3, "0.1", "0.2", "0.5");
    
    bool answers6[4];
    is_everlasting("25", answers6, 4, "0.0", "0.0000", "1.0", "0.0000001");
    print_results("25", answers6, 4, "0.0", "0.0000", "1.0", "0.0000001");
    
    return 0;
}