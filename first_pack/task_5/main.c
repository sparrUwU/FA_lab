#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char *input_filename;
    char *output_filename;
    char case_flag;

    if (argc < 3 || argc > 4) {
        printf("Ошибка ввода: неправильное количество аргументов\n");
        return 0;
    }

    if (argv[1][0] != '-' || argv[1][0] != '/') {
        printf("Ошибка ввода: флаг должен начинаться с символа \'-\' или \'/\'\n");
        return 0;
    }

    if (argv[1][1] == 'n' && argc == 4) {
        input_filename = argv[2];
        output_filename = argv[3];
        case_flag = argv[1][2];
    } else {
        input_filename = argv[2];
        output_filename = "out_";
        strcat(output_filename, input_filename);
        case_flag = argv[1][1];
    }

    FILE * fp_in = fopen(input_filename, "r");
    if (fp_in == NULL) {
        printf("Ошибка открытия входного файла");
        return 0;
    }

    FILE * fp_out = fopen(output_filename, "w");
    if (fp_in == NULL) {
        printf("Ошибка открытия выходного файла");
        return 0;
    }


    switch (case_flag)
    {
    case 'd':
        /* code */
        break;
    
    case 'i':
        /* code */
        break;
    
    case 's':
        /* code */
        break;

    case 'a':
        /* code */
        break;

    default:
        break;
    }
    
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}