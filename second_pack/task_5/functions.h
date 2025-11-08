#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define STRING_LENGTH 80

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR,
    OPEN_FILE_ERROR,
    MEMORY_ALLOCATION_ERROR
} status_code;

int is_readable_char(char c);
int count_words(const char *line);
status_code split_into_words(const char *line, char words[][STRING_LENGTH + 1], int max_words, int *actual_count);
status_code format_line(const char *input_line, char result[][STRING_LENGTH + 1], int len, int *actual_len);
status_code process_files(const char *input_filename, const char *output_filename);

#endif