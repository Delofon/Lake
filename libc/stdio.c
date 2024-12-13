#include <stdarg.h>

#include <arch/i386/vga.h>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef enum
{
    MODE_SCAN = 0,
    MODE_FLAGS,
    MODE_WIDTH,
    //MODE_PRECISION,
    MODE_LENGTH,
    MODE_CONVERSION,

    MODE_NUM
} mode_e;

typedef enum
{
    PADDING_SPACE,
    PADDING_ZERO,
    PADDING_RIGHT
} padding_e;

typedef enum
{
    POS_NONE,
    POS_BLANKS,
    POS_PLUS
} pos_e;

typedef enum
{
    LEN_INT,
    LEN_CHAR,
    LEN_SHORT,
    LEN_LONG,
    LEN_LONGLONG,
    LEN_LONGDOUBLE,
    LEN_INTMAX,
    LEN_SIZET,
    LEN_PTRDIFF
} len_e;

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

static inline int pad(padding_e padding, int num)
{
    if(num <= 0)
        return 0;

    char c;

    switch(padding)
    {
        case PADDING_SPACE:
        case PADDING_RIGHT:
            c = ' ';
            break;
        case PADDING_ZERO:
            c = '0';
            break;
        default:
            return -1;

    }

    for(int i = 0; i < num; i++)
    {
        putchar(c);
    }

    return num;
}

static inline int vprintf_d(int d, padding_e padding, int width)
{
    int bytes = 0;
    char s[11] = {0};
    s[0] = '0';

    char *p = s;
    if(d == 0)
    {
        bytes++;
        p++;
    }

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

    if(padding != PADDING_RIGHT)
        pad(padding, width - sz);

    vga_puts(s);

    if(padding == PADDING_RIGHT)
        pad(padding, width - sz);

    return bytes;
}

static inline int vprintf_u(unsigned int d, padding_e padding, int width)
{
    int bytes = 0;
    char s[11] = {0};
    s[0] = '0';

    char *p = s;
    if(d == 0)
    {
        bytes++;
        p++;
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

    if(padding != PADDING_RIGHT)
        pad(padding, width - sz);

    vga_puts(s);

    if(padding == PADDING_RIGHT)
        pad(padding, width - sz);

    return bytes;
}

static inline int vprintf_x(unsigned int ud, padding_e padding, int width)
{
    const char dig[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    int bytes = 0;
    char s[9] = {0};
    s[0] = '0';

    char *p = s;
    if(ud == 0)
    {
        bytes++;
        p++;
    }

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

    if(padding != PADDING_RIGHT)
        pad(padding, width - sz);

    vga_puts(s);

    if(padding == PADDING_RIGHT)
        pad(padding, width - sz);

    return bytes;
}

static inline int vprintf_s(const char *s)
{
    int bytes = strlen(s); // we pray to all computer gods that the user supplied string is null-terminated
    vga_puts(s);
    return bytes;
}

static inline void mode_cycle(mode_e *mode)
{
    (*mode)++;
    *mode %= MODE_NUM;
}

// TODO: properly test this against glibc printf
int vprintf(const char *format, va_list vargs)
{
    int bytes = 0;

    mode_e mode = MODE_SCAN;
    padding_e padding = PADDING_SPACE;
    pos_e pos = POS_NONE;

    char widthbuf[16] = {0};
    char *pbuf = widthbuf;
    int width = 0;

    len_e len = LEN_INT;

    while(*format)
    {
        const char c = *(format);

        switch(mode)
        {
            case MODE_SCAN:
                if(c == '%')
                {
                    mode_cycle(&mode);
                }
                else
                {
                    putchar(c);
                    bytes++;
                }
                format++;
                break;
            case MODE_FLAGS:
                switch(c)
                {
                    case '0':
                        padding = PADDING_ZERO;
                        format++;
                        break;
                    case '-':
                        padding = PADDING_RIGHT;
                        format++;
                        break;
                    case ' ':
                        pos = POS_BLANKS;
                        format++;
                        break;
                    case '+':
                        pos = POS_PLUS;
                        format++;
                        break;

                    default:
                        mode_cycle(&mode);
                        break;
                }
                break;
            case MODE_WIDTH:
                if(c > '0' && c <= '9')
                {
                    *(pbuf++) = c;
                    format++;
                }
                else
                {
                    *pbuf = 0;
                    pbuf = widthbuf;
                    width = atoi(widthbuf);
                    mode_cycle(&mode);
                }
                break;
            case MODE_LENGTH:
                switch(c)
                {
                    case 'h':
                        {
                            const char c1 = *(format+1);
                            if(c1 == 'h')
                            {
                                len = LEN_CHAR;
                                format++;
                            }
                            else
                            {
                                len = LEN_SHORT;
                            }
                        }
                        format++;
                        break;
                    case 'l':
                        {
                            const char c1 = *(format+1);
                            if(c1 == 'l')
                            {
                                len = LEN_LONGLONG;
                                format++;
                            }
                            else
                            {
                                len = LEN_LONG;
                            }
                        }
                        format++;
                        break;
                    case 'L':
                        len = LEN_LONGDOUBLE;
                        format++;
                        break;
                    case 'j':
                        len = LEN_INTMAX;
                        format++;
                        break;
                    case 'z':
                        len = LEN_SIZET;
                        format++;
                        break;
                    case 't':
                        len = LEN_PTRDIFF;
                        format++;
                        break;

                    default:
                        mode_cycle(&mode);
                        break;
                }
                break;
            case MODE_CONVERSION:
                switch(c)
                {
                    case 'd':
                        bytes += vprintf_d(va_arg(vargs, int), padding, width);
                        format++;
                        break;
                    case 'u':
                        bytes += vprintf_u(va_arg(vargs, unsigned int), padding, width);
                        format++;
                        break;
                    case 'x':
                        bytes += vprintf_x(va_arg(vargs, unsigned int), padding, width);
                        format++;
                        break;
                    case 's':
                        bytes += vprintf_s(va_arg(vargs, const char *));
                        format++;
                        break;
                    case 'p':
                        putchar('0'); putchar('x'); bytes += 2;
                        bytes += vprintf_x(va_arg(vargs, unsigned int), PADDING_ZERO, 8);
                    case '%':
                        putchar('%');
                        bytes++;
                        format++;
                        break;
                    default:
                        break;
                }
                mode_cycle(&mode);
                break;

            case MODE_NUM:
            default:
                break;
        }
    }
    return bytes;
}

