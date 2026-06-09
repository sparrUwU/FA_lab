#include <stdio.h>
#include <limits.h>
#include "functions.h"
#define MAX_OUT 33

int main() {
    char str[256];
    long p;
    long number;
    int p_i;
    int number_i;
    char answer[MAX_OUT];

    printf("Введите p (2, 4, 8, 16, 32): ");
    if (scanf("%s", str) != 1) {
        printf("Ошибка ввода p\n");
        return 0;
    }

    status_code convert_return = string_to_int(str, &p);
    if (convert_return != OK || p > INT_MAX || p < INT_MIN) {
        printf("Переполнение\n");
        return 0;
    }
    p_i = (int)p;


    printf("Введите число: ");
    if (scanf("%s", str) != 1) {
        printf("Ошибка ввода числа\n");
        return 0;
    }

    convert_return = string_to_int(str, &number);
    if (convert_return != OK || number > INT_MAX || number < INT_MIN) {
        printf("Переполнение\n");
        return 0;
    }
    number_i = (int)number;

    status_code status;

    status = convert_to_p(p_i, &number_i, answer);

    if (status != OK) {
        printf("Ошибка ввода p\n");
        return 0;
    }

    printf("Результат: %s\n", answer);

    return 0;
}
