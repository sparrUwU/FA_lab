#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"


int is_readable_char(char c) {
    return isprint((unsigned char)c) && (unsigned char)c != ' ';
}

int count_words(const char *line) {
    if (!line) return 0;
    
    int count = 0;
    int len = strlen(line);
    int i = 0;
    
    while (i < len) {
        while (i < len && !is_readable_char(line[i])) i++;
        if (i >= len) break;
        
        while (i < len && is_readable_char(line[i])) i++;
        count++;
    }
    
    return count;
}

status_code split_into_words(const char *line, char words[][STRING_LENGTH + 1], int max_count, int *actual_count) {
    if (!line || !words || !actual_count) return INPUT_ERROR;
    
    *actual_count = 0;
    int len = strlen(line);
    int i = 0;
    
    while (i < len && *actual_count < max_count) {
        while (i < len && line[i] == ' ') i++;
        if (i >= len) break;
        int start = i;

        while (i < len && is_readable_char(line[i])) i++;
        int word_len = i - start;
        
        if (word_len > 0 && word_len <= STRING_LENGTH) {
            strncpy(words[*actual_count], line + start, word_len);
            words[*actual_count][word_len] = '\0';
            (*actual_count)++;
        }
    }
    
    return OK;
}

status_code format_line(const char *input_line, char result[][STRING_LENGTH + 1], int max_lines, int *actual_len) {
    if (!input_line || !result || !actual_len) return INPUT_ERROR;
    
    int input_len = strlen(input_line);
    if (input_len == 0) {
        *actual_len = 0;
        return INPUT_ERROR;
    }
    
    if (input_len <= STRING_LENGTH) {
        strcpy(result[0], input_line);
        *actual_len = 1;
        return OK;
    }
    
    int max_count = count_words(input_line);
    if (max_count == 0) {
        *actual_len = 0;
        return OK;
    }
    
    char (*words)[STRING_LENGTH + 1] = malloc(max_count * (STRING_LENGTH + 1));
    if (!words) {
        return MEMORY_ALLOCATION_ERROR;
    }
    
    int actual_count;
    status_code split_result = split_into_words(input_line, words, max_count, &actual_count);
    
    if (split_result != OK || actual_count == 0) {
        free(words);
        *actual_len = 0;
        return OK;
    }
    
    *actual_len = 0;
    int word_index = 0;
    
    while (*actual_len < max_lines && word_index < actual_count) {
        int total_chars = 0;
        int total_words = 0;
        int line_start_index = word_index;
        
        while (word_index < actual_count) {
            int word_len = strlen(words[word_index]);
            int needed_space = word_len + (total_words > 0 ? 1 : 0);
            
            if (total_chars + needed_space <= STRING_LENGTH) {
                total_chars += needed_space;
                total_words++;
                word_index++;
            } else {
                break;
            }
        }
        
        if (total_words == 0 && word_index < actual_count) {
            result[*actual_len][0] = '\0';
            (*actual_len)++;
            word_index++;
            continue;
        }
        
        if (total_words == 0) {
            break;
        }
        
        int total_word_chars = 0;
        for (int i = 0; i < total_words; i++) {
            total_word_chars += strlen(words[line_start_index + i]);
        }
        
        int total_spaces_needed = STRING_LENGTH - total_word_chars;
        int gaps = total_words - 1;
        
        if (gaps <= 0) {
            strcpy(result[*actual_len], words[line_start_index]);
        } else {
            int base_spaces = total_spaces_needed / gaps;
            int extra_spaces = total_spaces_needed % gaps;
            
            int pos = 0;
            for (int i = 0; i < total_words; i++) {
                int word_len = strlen(words[line_start_index + i]);
                strcpy(result[*actual_len] + pos, words[line_start_index + i]);
                pos += word_len;
                
                if (i < total_words - 1) {
                    int spaces_to_add = base_spaces;
                    if (i < extra_spaces) {
                        spaces_to_add++;
                    }
                    
                    for (int j = 0; j < spaces_to_add; j++) {
                        result[*actual_len][pos++] = ' ';
                    }
                }
            }
            result[*actual_len][pos] = '\0';
        }
        
        (*actual_len)++;
    }

    free(words);
    return OK;
}

status_code process_files(const char *input_filename, const char *output_filename) {
    if (!input_filename || !output_filename) {
        return INPUT_ERROR;
    }
    
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        return OPEN_FILE_ERROR;
    }
    
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return OPEN_FILE_ERROR;
    }
    
    char *line = NULL;
    size_t line_size = 0;
    ssize_t read;
    int success = 1;
    
    while ((read = getline(&line, &line_size, input_file)) != -1) {
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
            read--;
        }
        
        if (read == 0) {
            fprintf(output_file, "\n");
            continue;
        }
        
        int max_lines_count = read / STRING_LENGTH + 1;
        int actual_lines_count = 0;
        char (*formatted_lines)[STRING_LENGTH + 1] = malloc(max_lines_count * (STRING_LENGTH + 1));
        status_code result = format_line(line, formatted_lines, max_lines_count, &actual_lines_count);
        
        if (result == OK) {
            for (int i = 0; i != actual_lines_count; ++i) {
                fprintf(output_file, "%s\n", formatted_lines[i]);
            }
        }

        free(formatted_lines);
    }
    
    free(line);
    fclose(input_file);
    fclose(output_file);
    
    return OK;
}