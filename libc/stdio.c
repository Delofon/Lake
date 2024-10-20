#include <stdarg.h>

#include <arch/i386/vga.h>

#include "stdio.h"

int putchar(int c)
{
    vga_putchar(c);
}

int printf(const char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);

    int ret = vprintf(format, vargs);

    va_end(vargs);

    return ret;
}

int vprintf(const char *format, va_list vargs)
{
    // TODO: vprintf
    vga_puts(format);
}

