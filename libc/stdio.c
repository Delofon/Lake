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

static inline int vprintf_u(unsigned int d)
{
    int bytes = 0;
    char s[11] = {0};
    s[0] = '0';

    char *p = s;
    if(d == 0) bytes++;

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

static inline int vprintf_d(int d)
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

static inline int vprintf_x(int d)
{
    const char dig[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    unsigned int ud = (unsigned int) d;

    int bytes = 0;
    char s[9] = {0};
    s[0] = '0';

    char *p = s;
    if(ud == 0) bytes++;

    while(ud != 0)
    {
        *(p++) = dig[ud & 0xf];
        ud >>= 4;
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

static inline int vprintf_s(const char *s)
{
    int bytes = strlen(s); // we pray to all computer gods that the user supplied string is null-terminated
    vga_puts(s);
    return bytes;
}

int vprintf(const char *format, va_list vargs)
{
    int bytes = 0;
    while(*format)
    {
        const char c  = *(format);
        const char c1 = *(format+1);
        if(c == '%')
        {
            switch(c1)
            {
                case 'd':
                    bytes += vprintf_d(va_arg(vargs, int));
                    format++;
                    break;
                case 'u':
                    bytes += vprintf_u(va_arg(vargs, unsigned int));
                    format++;
                    break;
                case 'x':
                    bytes += vprintf_x(va_arg(vargs, int));
                    format++;
                    break;
                case 's':
                    bytes += vprintf_s(va_arg(vargs, const char *));
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
            putchar(c);
            bytes++;
        }
        format++;
    }
    return bytes;
}

