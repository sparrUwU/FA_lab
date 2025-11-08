#ifndef OVERPRINTF_H
#define OVERPRINTF_H

#include <stdio.h>
#include <stdarg.h>

int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);
int voverfprintf(FILE *stream, const char *format, va_list args);
int voversprintf(char *str, const char *format, va_list args);

int roman(FILE *stream, int value);
int zeckendorf(FILE *stream, unsigned int value);
int base_lower(FILE *stream, int value, int base);
int base_upper(FILE *stream, int value, int base);
int from_base_lower(FILE *stream, const char *str, int base);
int from_base_upper(FILE *stream, const char *str, int base);
int memory_dump_int_file(FILE *stream, int value);
int memory_dump_uint_file(FILE *stream, unsigned int value);
int memory_dump_float_file(FILE *stream, float value);
int memory_dump_double_file(FILE *stream, double value);

int value_to_roman(int value, char *buffer);
int value_to_zeckendorf(unsigned int value, char *buffer);
int value_to_base(int value, int base, char *buffer, int uppercase);
int value_from_base(const char *str, int base, int uppercase);
int from_base_to_string(const char *str, int base, int uppercase, char *buffer, int buffer_size);
int memory_dump_to_string(char *str, int str_size, const void *value, size_t size);
int memory_dump_int_string(char *str, int str_size, int value);
int memory_dump_uint_string(char *str, int str_size, unsigned int value);
int memory_dump_float_string(char *str, int str_size, float value);
int memory_dump_double_string(char *str, int str_size, double value);

#endif