#include <stdio.h>
#include <string.h>
#include "overprintf.h"

int main() {
    char buffer[512];
    
    printf("1. Демонстрация overfprintf (вывод в файл)\n");
    FILE *file = fopen("output.txt", "w");
    if (file) {
        overfprintf(file, "Overfprintf:\n\n");

        overfprintf(file, "Римские цифры:\n");
        overfprintf(file, "  2023 = %Ro\n", 2023);
        overfprintf(file, "  49 = %Ro\n", 49);
        overfprintf(file, "  99 = %Ro\n\n", 99);

        overfprintf(file, "Цекендорфово представление:\n");
        overfprintf(file, "  20 = %Zr\n", 20);
        overfprintf(file, "  15 = %Zr\n", 15);
        overfprintf(file, "  7 = %Zr\n\n", 7);

        overfprintf(file, "Системы счисления:\n");
        overfprintf(file, "  255 в 16-ричной (нижний): %Cv\n", 255, 16);
        overfprintf(file, "  255 в 16-ричной (верхний): %CV\n", 255, 16);
        overfprintf(file, "  42 в 2-ичной: %Cv\n", 42, 2);
        overfprintf(file, "  -100 в 8-ричной: %Cv\n\n", -100, 8);

        overfprintf(file, "Перевод из систем счисления:\n");
        overfprintf(file, "  \"ff\" из 16-ричной: %to\n", "ff", 16);
        overfprintf(file, "  \"FF\" из 16-ричной: %TO\n", "FF", 16);
        overfprintf(file, "  \"1010\" из 2-ичной: %to\n\n", "1010", 2);

        overfprintf(file, "Дампа памяти целых чисел:\n");
        overfprintf(file, "  int 305419896: %mi\n", 305419896);
        overfprintf(file, "  unsigned int 305419896: %mu\n", 305419896u);
        overfprintf(file, "  int -1: %mi\n\n", -1);

        overfprintf(file, "Дампа памяти вещественных чисел:\n");
        overfprintf(file, "  float 3.14: %mf\n", 3.14f);
        overfprintf(file, "  double 2.71828: %md\n\n", 2.71828);

        overfprintf(file, "Комбинированный пример:\n");
        overfprintf(file, "Число %d = %Ro (рим.) = %Cv (16-рич.) = %Zr (Цекенд.)\n", 42, 42, 42, 16, 42);
        
        fclose(file);
    } else {
        printf("Ошибка создания файла\n");
    }
    
    printf("\n2. Демонстрация через oversprintf (вывод в строку):\n");

    oversprintf(buffer, "Римские цифры: 2023=%Ro, 49=%Ro, 99=%Ro", 2023, 49, 99);
    printf("%s\n", buffer);

    oversprintf(buffer, "Цекендорф: 20=%Zr, 15=%Zr, 7=%Zr", 20, 15, 7);
    printf("%s\n", buffer);

    oversprintf(buffer, "Системы счисления: 255(16 ниж.)=%Cv, 255(16 верх.)=%CV, 42(2)=%Cv", 255, 16, 255, 16, 42, 2);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Перевод: 'ff'(16)=%to, 'FF'(16)=%TO, '1010'(2)=%to", "ff", 16, "FF", 16, "1010", 2);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Дампа int: 305419896=%mi, unsigned= %mu", 305419896, 305419896u);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Дампа float: 3.14=%mf, double: 2.71828=%md", 3.14f, 2.71828);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Комбинированный: %d = %Ro = %Cv(16) = %Zr", 123, 123, 123, 16, 123);
    printf("%s\n", buffer);
    
    return 0;
}