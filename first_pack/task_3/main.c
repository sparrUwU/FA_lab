#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flags.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Недостаточно аргументов\n");
        return INPUT_ERROR;
    }
    
    if (argv[1][0] != '-' && argv[1][0] != '/') {
        printf("Флаг должен начинаться с '-' или '/'\n");
        return INPUT_ERROR;
    }

    status_code result;
    switch (argv[1][1]) {
    case 'q': {
        if (argc != 6) {
            printf("Для флага -q требуется 5 параметров (флаг, эпсилон, a, b, c)\n");
            return INPUT_ERROR;
        }
        
        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);
        
        solution_result results[6];
        
        if ((result = q_equation(epsilon, a, b, c, results)) != OK) {
            printf("Ошибка при решении уравнения\n");
            return result;
        }
        
        printf("Решения квадратного уравнения для всех перестановок коэффициентов:\n");
        for (int i = 0; i < 6; i++) {
            printf("Вариант %d: %s\n", i + 1, results[i].solutions);
        }
        break;
    }

    case 'm': {
        if (argc != 4) {
            printf("Для флага -m требуется 3 параметра (флаг, число1, число2)\n");
            return INPUT_ERROR;
        }
        
        char answer;
        
        if ((result = m_is_multiples(argv[2], argv[3], &answer)) == INPUT_ERROR) {
            if (answer == 'z') {
                printf("Деление на ноль\n");
            } else if (answer == 'f') {
                printf("Первое число меньше второго\n");
            }
            return result;
        }
        if (result == OVERFLOW_ERROR) {
            printf("Введены слишком большие числа\n");
            return result;
        }
        
        if (answer == '1') {
            printf("Число %s кратно числу %s\n", argv[2], argv[3]);
        } else {
            printf("Число %s НЕ кратно числу %s\n", argv[2], argv[3]);
        }
        break;
    }

    case 't': {
        if (argc != 6) {
            printf("Ошибка: для флага -t требуется 5 параметров (флаг, эпсилон, сторона1, сторона2, сторона3)\n");
            return INPUT_ERROR;
        }
        
        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);
        
        int is_right_triangle;
        
        if ((result = t_side_of_triangle(epsilon, a, b, c, &is_right_triangle)) != OK) {
            printf("Ошибка: некорректные длины сторон треугольника\n");
            return result;
        }
        
        if (is_right_triangle) {
            printf("Треугольник со сторонами %.2f, %.2f, %.2f является прямоугольным\n", a, b, c);
        } else {
            printf("Треугольник со сторонами %.2f, %.2f, %.2f НЕ является прямоугольным\n", a, b, c);
        }
        break;
    }

    default:
        printf("Ошибка ввода: несуществующее значение флага '%c'\n", argv[1][1]);
        return INPUT_ERROR;
    }
    
    return OK;
}