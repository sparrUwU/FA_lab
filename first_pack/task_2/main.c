#include <stdio.h>
#include <math.h>
#include <string.h>
#include "functions.h"

int main(int argc, char **argv) {
    if (argc != 1) {
        printf("Ошибка ввода.\n");
        return INPUT_ERROR;
    }

    char str_input[100];
    long T;
    fgets(str_input, sizeof(str_input), stdin);

    str_input[strcspn(str_input, "\n")] = '\0';

    status_code convert_return = string_to_int(str_input, &T);
    if (convert_return != OK || T <= 0) {
        printf("Неверное количество запросов.\n");
        return convert_return;
    }

    long numbers[T];

    int i = 0;
    while (i != T) {
        if (fgets(str_input, sizeof(str_input), stdin) == NULL) {
            printf("Ошибка ввода.\n");
            return INPUT_ERROR;
        }

        long input;
        str_input[strcspn(str_input, "\n")] = '\0';
        convert_return = string_to_int(str_input, &input);
        if (convert_return != OK || input <= 0) {
            printf("Введен неверный номер.\n");
            return convert_return;
        }

        if (input > 10000) {
            printf("Слишком большой номер. Он не должен превышать 10000.\n");
            return INPUT_ERROR;
        }

        numbers[i++] = input;
    }

    Er_prime(0);

    for (int k = 0; k < T; ++k) {
        printf("%ld\n", Er_prime(numbers[k]));
    } 

    Er_prime(-1);
    return OK;
}