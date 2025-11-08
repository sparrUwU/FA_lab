#ifndef OVERSCANF_H
#define OVERCSANF_H

#include <stdio.h>
#include <stdarg.h>

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(char *str, const char *format, ...);
int voverfscanf(FILE *stream, const char *format, va_list args);
int voversscanf(char *str, const char *format, va_list args);

int parse_roman(const char *str, int *consumed);
int parse_zeckendorf(const char *str, int *consumed);
int parse_base(const char *str, int base, int *consumed, int uppercase);

#endif