#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define VAR_COUNT 26
#define MAX_LINE 256

void remove_spaces(char *str) {
    char *p = str;
    char *q = str;

    while (*q) {
        if (!isspace(*q)) *p++ = *q;
        q++;
    }

    *p = '\0';
}

int is_simple_assignment(const char *expr) {
    if (strlen(expr) == 0) return 0;

    if (isalpha(expr[0]) && expr[1] == 0) return 1;

    int i = 0;
    if (expr[0] == '-' || expr[0] == '+') i = 1;

    for (; expr[i]; i++) {
        if (!isdigit(expr[i])) return 0;
    }

    return 1;
}

int eval_expr(const int *vars, const char *expr, int *result) {
    int numbers[128];
    char ops[128];
    int n_top = -1, o_top = -1;
    int i = 0;

    while (expr[i]) {
        if (expr[i] == '+' || expr[i] == '-') {
            if (i == 0 || strchr("+-*/^", expr[i-1])) {
                int sign = (expr[i] == '-') ? -1 : 1;
                i++;
                int num = 0;

                if (isalpha(expr[i])) {
                    int idx = expr[i] - 'A';

                    if (vars[idx] == -1) {
                        return -1;
                    }

                    num = vars[idx];
                    i++;
                } else if (isdigit(expr[i])) {
                    while (isdigit(expr[i])) {
                        num = num * 10 + (expr[i] - '0');
                        i++;
                    }
                } else {
                    return -1;
                }

                numbers[++n_top] = sign * num;
            } else {
                ops[++o_top] = expr[i];
                i++;
            }
        } else if (isdigit(expr[i])) {
            int num = 0;

            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }

            numbers[++n_top] = num;
        } else if (isalpha(expr[i])) {
            int idx = expr[i] - 'A';
            if (vars[idx] == -1) {
                return -1;
            }
            
            numbers[++n_top] = vars[idx];
            i++;
        } else if (strchr("*/^", expr[i])) {
            ops[++o_top] = expr[i];
            i++;
        } else {
            i++;
        }
    }

    for (int j = 0; j <= o_top; j++) {
        if (ops[j] == '^') {
            numbers[j] = (int)pow(numbers[j], numbers[j + 1]);
            for (int k = j + 1; k < n_top; k++) numbers[k] = numbers[k + 1];
            for (int k = j; k < o_top; k++) ops[k] = ops[k + 1];
            n_top--;
            o_top--;
            j--;
        }
    }

    for (int j = 0; j <= o_top; j++) {
        if (ops[j] == '*' || ops[j] == '/') {
            if (ops[j] == '*') numbers[j] = numbers[j] * numbers[j + 1];
            else numbers[j] = numbers[j] / numbers[j + 1];
            for (int k = j + 1; k < n_top; k++) numbers[k] = numbers[k + 1];
            for (int k = j; k < o_top; k++) ops[k] = ops[k + 1];
            n_top--;
            o_top--;
            j--;
        }
    }

    for (int j = 0; j <= o_top; j++) {
        if (ops[j] == '+') numbers[j] = numbers[j] + numbers[j + 1];
        else if (ops[j] == '-') numbers[j] = numbers[j] - numbers[j + 1];
        for (int k = j + 1; k < n_top; k++) numbers[k] = numbers[k + 1];
        for (int k = j; k < o_top; k++) ops[k] = ops[k + 1];
        n_top--;
        o_top--;
        j--;
    }

    *result = numbers[0];
    return 0;
}

void log_trace(FILE *log_file, const int *vars, int line_number, const char *line, const char *operation) {
    fprintf(log_file, "[%d] %s\t| ", line_number, line);
    int first = 1;
    for (int i = 0; i < VAR_COUNT; i++) {
        if (vars[i] != -1) {
            if (!first) fprintf(log_file, ", ");
            fprintf(log_file, "%c=%d", 'A' + i, vars[i]);
            first = 0;
        }
    }
    fprintf(log_file, " | %s\n", operation);
    fflush(log_file);
}

int main() {
    int vars[VAR_COUNT + 1];
    FILE *log_file;

    char line[MAX_LINE];
    int line_number = 0;

    for (int i = 0; i < VAR_COUNT; i++) vars[i] = -1;

    log_file = fopen("trace.log", "w");
    if (!log_file) {
        printf("Ошибка открытия файла трассировки\n");
        return 0;
    }

    printf("Начало работы программы (Ctrl+Z для остановки):\n");
    while (fgets(line, sizeof(line), stdin)) {
        line_number++;
        line[strcspn(line, "\n")] = 0;
        char orig_line[MAX_LINE];
        strcpy(orig_line, line);
        remove_spaces(line);

        if (strlen(line) == 0) continue;

        if (strncmp(line, "print(", 6) == 0 && line[strlen(line)-1] == ')') {
            char var = line[6];

            if (var < 'A' || var > 'Z' || vars[var - 'A'] == -1 || strlen(line) != 8) {
                printf("Ошибка: неправильно использована функция вывода\n");
                continue;
            }

            printf("%d\n", vars[var - 'A']);
            log_trace(log_file, vars, line_number, orig_line, "Print");
        } else if (strchr(line, '=')) {
            char var = line[0];

            if (var < 'A' || var > 'Z') {
                printf("Ошибка: невалидное название переменной\n");
                continue;
            }

            char *expr = strchr(line, '=') + 1;
            int val;

            if (eval_expr(vars, expr, &val) == -1) {
                printf("Ошибка: невалидные символы в выражении\n");
                continue;
            }

            vars[var - 'A'] = val;

            const char *op_type = is_simple_assignment(expr) ? "Assignment" : "Arithmetic operation";
            log_trace(log_file, vars, line_number, orig_line, op_type);
        } else {
            printf("Ошибка: неизвестная команда\n");
        }
    }

    fclose(log_file);
    return 0;
}