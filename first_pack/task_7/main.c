#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Ошибка ввода: неправильное количество аргументов\n");
        return FILE_ERROR;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];
    
    FILE *input = fopen(input_filename, "r");
    if (input == NULL) {
        printf("Ошибка открытия входного файла\n");
        return FILE_ERROR;
    }
    
    FILE *output = fopen(output_filename, "w");
    if (output == NULL) {
        printf("Ошибка открытия выходного файла\n");
        fclose(input);
        return FILE_ERROR;
    }
    
    status_code result = process_file(input, output);
    
    fclose(input);
    fclose(output);
    
    if (result != OK) {
        fprintf(stderr, "Обработка завершена с ошибками (код: %d)\n", result);
    } else {
        fprintf(stderr, "Обработка завершена успешно\n");
    }
    
    printf("Результат в файле: %s\n", output_filename);
    return result;
}