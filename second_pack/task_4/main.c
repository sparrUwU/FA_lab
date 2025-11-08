#include <stdio.h>
#include <string.h>
#include "overscanf.h"

int main() {
    int roman_val, base_val1, base_val2, base_val3;
    unsigned int zeck_val;
    
    printf("1. Демонстрация overfscanf (ввод из файла)\n");
    FILE *file = fopen("input.txt", "r");
    if (file) {
        printf("Чтение из файла input.txt:\n");
        
        overfscanf(file, "%Ro", &roman_val);
        printf("Римские цифры: MMXXIII = %d\n", roman_val);
        
        overfscanf(file, "%Ro", &roman_val);
        printf("  XLIX = %d\n", roman_val);
        
        overfscanf(file, "%Ro", &roman_val);
        printf("  XCIX = %d\n", roman_val);
        
        overfscanf(file, "%Zr", &zeck_val);
        printf("Цекендорф: 01111 = %u\n", zeck_val);
        
        overfscanf(file, "%Zr", &zeck_val);
        printf("  010011 = %u\n", zeck_val);
        
        overfscanf(file, "%Zr", &zeck_val);
        printf("  0111 = %u\n", zeck_val);
        
        overfscanf(file, "%Cv", &base_val1, 16);
        printf("Системы счисления: ff = %d\n", base_val1);
        
        overfscanf(file, "%CV", &base_val2, 16);
        printf("  FF = %d\n", base_val2);
        
        overfscanf(file, "%Cv", &base_val3, 2);
        printf("  101010 = %d\n", base_val3);
        
        overfscanf(file, "%Cv", &base_val1, 8);
        printf("  -100 = %d\n", base_val1);
        
        fclose(file);
    } else {
        printf("Ошибка открытия файла input.txt\n");
    }
    
    printf("\n2. Демонстрация oversscanf (разбор строк):\n");

    oversscanf("MMXXIII", "%Ro", &roman_val);
    printf("Римские цифры: MMXXIII = %d\n", roman_val);
    
    oversscanf("XLIX", "%Ro", &roman_val);
    printf("  XLIX = %d\n", roman_val);
    
    oversscanf("XCIX", "%Ro", &roman_val);
    printf("  XCIX = %d\n", roman_val);

    oversscanf("101010", "%Zr", &zeck_val);
    printf("Цекендорф: 101010 = %u\n", zeck_val);
    
    oversscanf("100110", "%Zr", &zeck_val);
    printf("  100110 = %u\n", zeck_val);
    
    oversscanf("1010", "%Zr", &zeck_val);
    printf("  1010 = %u\n", zeck_val);

    oversscanf("ff", "%Cv", &base_val1, 16);
    printf("Системы счисления: 255(16 ниж.) = %d\n", base_val1);
    
    oversscanf("FF", "%CV", &base_val2, 16);
    printf("  255(16 верх.) = %d\n", base_val2);
    
    oversscanf("101010", "%Cv", &base_val3, 2);
    printf("  42(2) = %d\n", base_val3);
    
    oversscanf("-144", "%Cv", &base_val1, 8);
    printf("  -100(8) = %d\n", base_val1);
    
    return 0;
}