#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    printf("Введите строку: ");

    size_t capacity = 64;
    size_t length = 0;
    char *input = malloc(capacity);
    if (!input) {
        printf("Ошибка выделения памяти\n");
        return 0;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            input = realloc(input, capacity);
            if (!input) {
                printf("Ошибка выделения памяти\n");
                return 0;
            }
        }
        input[length++] = (char)c;
    }
    input[length] = '\0';

    if (check_brackets(input))
        printf("Скобки расставлены корректно.\n");
    else
        printf("Скобки расставлены неверно.\n");

    free(input);
    return 0;
}
