#include <stdio.h>
#include <string.h>
#include "functions.h"


int main() {
    char input_filename[256];
    char output_filename[256];
    

    printf("Введите путь к входному файлу: ");
    if (fgets(input_filename, 256, stdin) == NULL) {
        printf("Ошибка чтения входного файла\n");
        return 0;
    }
    
    printf("Введите путь к выходному файлу: ");
    if (fgets(output_filename, 256, stdin) == NULL) {
        printf("Ошибка чтения выходного файла\n");
        return 0;
    }
    
    input_filename[strcspn(input_filename, "\n")] = '\0';
    output_filename[strcspn(output_filename, "\n")] = '\0';
    
    int result = process_files(input_filename, output_filename);
    
    if (result == OK) {
        printf("Форматирование завершено успешно!\n");
    } else if (result == INPUT_ERROR) {
        printf("Введен пустой путь к файлу\n");
        return 0;
    } else if (result == OPEN_FILE_ERROR) {
        printf("Ошибка открытия файлов\n");
    }
    
    return 0;
}

/*
/mnt/c/Users/sparrowo/Documents/GitHub/FA_lab/second_pack/task_5/test1.txt
/mnt/c/Users/sparrowo/Documents/GitHub/FA_lab/second_pack/task_5/test2.txt
*/