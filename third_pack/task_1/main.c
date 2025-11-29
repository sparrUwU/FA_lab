#include <stdio.h>
#include "functions.h"
#define MAX_OUT 33

int main() {
    int p;
    int number;
    char answer[MAX_OUT];

    printf("Введите p (2, 4, 8, 16, 32): ");
    if (scanf("%d", &p) != 1) {
        printf("Ошибка ввода p\n");
        return 0;
    }

    printf("Введите число: ");
    if (scanf("%d", &number) != 1) {
        printf("Ошибка ввода числа\n");
        return 0;
    }

    status_code status;

    status = convert_to_p(p, &number, answer);

    if (status != OK) {
        printf("Ошибка ввода p\n");
        return 0;
    }

    printf("Результат: %s\n", answer);

    return 0;
}
