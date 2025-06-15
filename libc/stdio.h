#ifndef STDIO_H_
#define STDIO_H_

#include <stdarg.h>

int putchar(int c);
int printf(const char *format, ...);
int vprintf(const char *format, va_list vargs);

#endif

