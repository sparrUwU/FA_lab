#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Ошибка ввода.\n");
        return INPUT_ERROR;
    }

    const char *str_x = argv[1];
    const char *flag = argv[2];

    if ((flag[0] != '-' && flag[0] != '/') || strlen(flag) != 2) {
        printf("Неверный формат флага.\n");
        return INPUT_ERROR;
    }

    status_code result;
    switch (flag[1]) {
    case 'h': {
        long long x;
        status_code convert_return = string_to_int(str_x, &x);
        if (convert_return != OK) {
            printf("Ошибка при переводе строчного представления числа в целое.\n");
            return 0;
        }

        long long h[100];
        if ((result = h_finding_multiples(&x, h)) != OK) {
            printf("Ошибка ввода: число должно быть больше 0\n");
            return 0;
        }

        if (h[0] == 0) {
            printf("Чисел, кратных %lld, в пределах 100 нет\n", x);
            return 0;
        }

        printf("Числа, кратные %lld, в пределах 100: %lld", x, h[0]);
        int i = 1;
        while (h[i] != 0) {
            printf(", %lld", h[i]);
        }
        break;
    }

    case 'p': {
        long long x;
        status_code convert_return = string_to_int(str_x, &x);
        if (convert_return != OK) {
            printf("Ошибка при переводе строчного представления числа в целое.\n");
            return convert_return;
        }

        int ans;
        if ((result = p_is_composite(&x, &ans)) == INPUT_ERROR) {
            printf("Ошибка ввода: число должно быть больше 1\n");
        } else if (ans == 0) {
            printf("%lld - простое число", x);
        } else {
            printf("%lld - составное число", x);
        }
        break;
    }

    case 's': {
        char hex_result[256] = {0};
        
        if ((result = s_16_notation(str_x, hex_result)) != OK) {
            printf("Ошибка при переводе в 16-ричную систему\n");
            return result;
        }
        
        printf("Десятичное: %s -> Шестнадцатеричное: %s\n", str_x, hex_result);
        break;
    }

    case 'e': {
        long long x;
        status_code convert_return = string_to_int(str_x, &x);
        if (convert_return != OK) {
            printf("Ошибка: степень должна быть целым числом\n");
            return convert_return;
        }

        if (x < 1 || x > 10) {
            printf("Ошибка: степень должна быть в диапазоне от 1 до 10\n");
            return INPUT_ERROR;
        }

        long long results[101]; 
        status_code table_result = e_pow_table(&x, results); 
        
        if (table_result != OK) {
            printf("Ошибка при вычислении таблицы степеней\n");
            return table_result;
        }

        printf("Основание \\ Степень");
        for (long long power = 1; power <= x; power++) {
            printf("\t%lld", power);
        }
        printf("\n");

        int element_index = 0;
        for (long long base = 1; base <= 10; base++) {
            printf("%lld", base);
            for (long long power = 1; power <= x; power++) {
                printf("\t%lld", results[element_index++]);
            }
            printf("\n");
        }
        break;
    }

    case 'a': {
        long long x;
        status_code convert_return = string_to_int(str_x, &x);
        if (convert_return != OK) {
            printf("Ошибка: число должно быть целым\n");
            return convert_return;
        }

        long long sum;
        status_code sum_result = a_sum_to_x(&x, &sum);
        
        if (sum_result != OK) {
            if (sum_result == INPUT_ERROR) {
                printf("Ошибка: число должно быть положительным\n");
            } else if (sum_result == OVERFLOW_ERROR) {
                printf("Ошибка: переполнение при вычислении суммы\n");
            }
            return sum_result;
        }

        printf("Сумма натуральных чисел от 1 до %lld: %lld\n", x, sum);
        break;
    }

    case 'f': {
        long long x;
        status_code convert_return = string_to_int(str_x, &x);
        if (convert_return != OK) {
            printf("Ошибка при переводе строчного представления числа в целое.\n");
            return convert_return;
        }
        long long fact_result = 1; 
        if ((result = f_factorial(&x, &fact_result)) != OK) {
            printf("Произошла ошибка при выполнении функции.\n");
        } else {
            printf("Факториал %lld равен %lld\n", x, fact_result); 
        }
        break;
    }

    default:
        printf("Ошибка ввода: несуществующее значение флага.\n");
        return INPUT_ERROR;
    }

    return result;
}