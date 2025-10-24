#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char **argv) {
    char *input_filename;
    char output_filename[256];
    char case_flag;

    if (argc < 3 || argc > 4) {
        printf("Ошибка ввода: неправильное количество аргументов\n");
        return 0;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/') {
        printf("Ошибка ввода: флаг должен начинаться с символа \'-\' или \'/\'\n");
        return 0;
    }

    if (strlen(argv[1]) >= 3 && argv[1][1] == 'n' && argc == 4) {
        input_filename = argv[2];
        strcpy(output_filename, argv[3]);
        case_flag = argv[1][2];
    } else if (strlen(argv[1]) == 2 && argc == 3) {
        input_filename = argv[2];
        strcpy(output_filename, "out_");
        strcat(output_filename, input_filename);
        case_flag = argv[1][1]; 
    } else {
        printf("Ошибка ввода: неправильная комбинация флага и аргументов\n");
        return 0;
    }

    if (case_flag != 'd' && case_flag != 'i' && case_flag != 's' && case_flag != 'a') {
        printf("Ошибка ввода: неверный флаг\n");
        return 0;
    }

    FILE *fp_in = fopen(input_filename, "r");
    if (fp_in == NULL) {
        printf("Ошибка открытия входного файла\n");
        return 0;
    }

    FILE *fp_out = fopen(output_filename, "w");
    if (fp_out == NULL) {
        printf("Ошибка открытия выходного файла\n");
        fclose(fp_in);
        return 0;
    }

    status_code result = OK;

    switch (case_flag) {
        case 'd':
            result = d_delete_numbers(fp_in, fp_out);
            break;
        case 'i':
            result = i_count_latin(fp_in, fp_out);
            break;
        case 's':
            result = s_count_special(fp_in, fp_out);
            break;
        case 'a':
            result = a_to_ascii(fp_in, fp_out);
            break;
        default:
            printf("Неизвестный флаг\n");
            result = INPUT_ERROR;
            break;
    }

    fclose(fp_in);
    fclose(fp_out);

    if (result != OK) {
        printf("Ошибка при обработке файла\n");
        return 1;
    }

    printf("Результат в файле: %s\n", output_filename);
    return 0;
}