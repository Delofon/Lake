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

static inline int vprintf_int(va_list vargs)
{
    int bytes = 0;
    int d = va_arg(vargs, int);
    int pow = 1;

    if(d < 0)
    {
        vga_putchar('-');
        d *= -1;
        bytes++;
    }

    {
        int dd = d;
        for(; dd > 0; pow *= 10)
            dd /= 10;
        pow /= 10;
    }

    while(pow != 0)
    {
        char c = (d / pow) % 10;
        pow /= 10;
        vga_putchar(c + '0');
        bytes++;
    }

    return bytes;
}

static inline int vprintf_string(va_list vargs)
{
    const char *s = va_arg(vargs, const char *);
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
                    bytes += vprintf_int(vargs);
                    format++;
                    break;
                case 's':
                    bytes += vprintf_string(vargs);
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

