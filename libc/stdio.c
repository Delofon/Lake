#include <stdarg.h>

#include <arch/i386/vga.h>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int putchar(int c)
{
    vga_putchar(c);
    return c;
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
    char s[11] = {0};
    s[0] = '0';

    char *p = s;
    if(d == 0) bytes++;

    if(d < 0)
    {
        d = -d;
        vga_putchar('-');
        bytes++;
    }

    while(d != 0)
    {
        *(p++) = (d % 10) + '0';
        d /= 10;
    }

    size_t sz = p - s;
    bytes += sz;
    for(size_t i = 0; i < sz / 2; i++)
    {
        char tmp = s[i];
        s[i] = s[sz - i - 1];
        s[sz - i - 1] = tmp;
    }

    vga_puts(s);

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

