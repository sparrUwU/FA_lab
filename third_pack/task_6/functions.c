#include <stdio.h>
#include <stdlib.h>

int check_brackets(const char *str) {
    if (!str) return 0;

    size_t capacity = 16;
    size_t size = 0;
    char *stack = malloc(capacity * sizeof(char));
    if (!stack) return 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '(' || c == '[' || c == '{' || c == '<') {
            if (size == capacity) {
                capacity *= 2;
                stack = realloc(stack, capacity * sizeof(char));
                if (!stack) return 0;
            }
            stack[size++] = c;
        } else if (c == ')' || c == ']' || c == '}' || c == '>') {
            if (size == 0) {
                free(stack);
                return 0;
            }
            char top = stack[size - 1];
            int ok = 0;
            if (c == ')' && top == '(') ok = 1;
            if (c == ']' && top == '[') ok = 1;
            if (c == '}' && top == '{') ok = 1;
            if (c == '>' && top == '<') ok = 1;
            if (!ok) {
                free(stack);
                return 0;
            }
            size--;
        }
    }

    int result = (size == 0);
    free(stack);
    return result;
}