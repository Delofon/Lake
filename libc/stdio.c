#include <stdarg.h>

#include <arch/i386/vga.h>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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

static inline int vprintf_int(int d)
{
    int bytes = 0;
    int sgn = 1;
    char s[11] = {0};
    char *p = s+9;

    if(d < 0)
    {
        vga_putchar('-');
        sgn = -1;
        bytes++;
    }

    while(d != 0)
    {
        *(p--) = (d % 10)*sgn + '0';
        d /= 10;
        bytes++;
    }

    vga_puts(++p);

    return bytes;
}

static inline int vprintf_string(const char *s)
{
    int bytes = strlen(s); // unsafe?
    vga_puts(s);
    return bytes;
}

int vprintf(const char *format, va_list vargs)
{
    int bytes = 0;
    while(*format)
    {
        const char c = *format;
        const char c1 = *(format+1);
        if(c == '%')
        {
            switch(c1)
            {
                case 'd':
                    bytes += vprintf_int(va_arg(vargs, int));
                    format++;
                    break;
                case 's':
                    bytes += vprintf_string(va_arg(vargs, const char *));
                    format++;
                    break;
                case '%':
                    putchar('%');
                    bytes++;
                    format++;
                    break;
                default:
                    break;
            }
        }
        else
        {
            vga_putchar(c);
            bytes++;
        }
        format++;
    }
    return bytes;
}

