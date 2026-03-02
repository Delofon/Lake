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
    NIL = 0,

    INT, DBL, PTR, STR,
    CHAR, SHORT,
    LONG, LLONG,
    LDBL,

    INTMAX, SIZET, PTRDIFF,

    NUM_ARGS
} type_e;

typedef struct
{
    union {
        uintmax_t i;
        long double ldbl;
        void *p;
    };
    type_e type;
} arg_t;

static inline void pop(arg_t *arg, va_list *va)
{
    switch(arg->type) {
    case CHAR:
    case SHORT:
    case INT:
    case LONG:
        arg->i = va_arg(*va, int);
        break;
    case LLONG:
    case INTMAX:
    case SIZET:
    case PTRDIFF:
        arg->i = va_arg(*va, long long);
        break;
    case DBL:
        arg->ldbl = va_arg(*va, double);
        break;
    case LDBL:
        arg->ldbl = va_arg(*va, long double);
        break;
    case STR:
    case PTR:
        arg->p = va_arg(*va, void *);
        break;

    case NIL:
    case NUM_ARGS:
    default:
        break;
    }
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
static inline void rev(char *s, size_t sz)
{
    for(size_t i = 0; i < sz / 2; i++)
    {
        char tmp = s[i];
        s[i] = s[sz - i - 1];
        s[sz - i - 1] = tmp;
    }
}

const char dig[32] = "0123456789abcdef0123456789ABCDEF";
const char *DIG = dig+16;
static inline int fmt_int(arg_t arg, int conv, padding_e padding, int width)
{
    int bytes = 0;
    char s[21] = {0}; char *p = s;
    s[0] = '0';

    long long ll = arg.i;
    unsigned long ul = arg.i;
    unsigned long long ull = arg.i;

    if(ull == 0)
    {
        bytes++;
        p++;
    }

    if(ll < 0 && conv == 0)
    {
        switch(arg.type)
        {
            case INT:
            case LONG:
            case LLONG:
                // FIXME: write into s[] instead
                putchar('-');
                bytes++;
                ull = -ll;
                break;
            default:
                break;
        }
    }

    switch(arg.type)
    {
        case INT:
        case LONG:
            ull = ul;
            break;
        default:
            break;
    }

    while(ull != 0)
    {
        if(conv == 1)
        {
            *(p++) = dig[ull & 0xf];
            ull >>= 4;
        }
        else if(conv == 2)
        {
            *(p++) = DIG[ull & 0xf];
            ull >>= 4;
        }
        else if(conv == 0)
        {
            *(p++) = dig[ull % 10];
            ull /= 10;
        }
    }

    size_t sz = p - s;
    bytes += sz;
    rev(s, sz);

    if(padding != PADDING_RIGHT)
        pad(padding, width - sz);

    vga_puts(s);

    if(padding == PADDING_RIGHT)
        pad(padding, width - sz);

    return bytes;
}

static inline int fmt_str(const char *s)
{
    int bytes = strlen(s); // we pray to all computer gods that the user supplied string is null-terminated
    vga_puts(s);
    return bytes;
}

// TODO: properly test this against glibc printf
int vprintf(const char *fmt, va_list va)
{
    int bytes = 0;

    mode_e mode = MODE_SCAN;

    padding_e padding = PADDING_SPACE;
    pos_e pos = POS_NONE;
    int width = 0;

    arg_t arg = { .i = 0, .type = INT };

    while(*fmt)
    {
        if(mode == MODE_SCAN)
        {
            if(*fmt != '%')
            {
                bytes++;
                putchar(*fmt);
                fmt++;
            }
            else
                fmt++, mode = MODE_FLAGS;
        }
        else if(mode == MODE_FLAGS)
        {
            if(*fmt == '%')
            {
                bytes++;
                putchar(*fmt);
                fmt++;
                mode = MODE_SCAN;
            }
            else
            switch(*(fmt++))
            {
                case '0': padding = PADDING_ZERO; break;
                case '-': padding = PADDING_RIGHT; break;
                case ' ': pos = POS_BLANKS; break;
                case '+': pos = POS_PLUS; break;
                default:
                    fmt--;
                    mode = MODE_WIDTH;
                    break;
            }
        }
        else if(mode == MODE_WIDTH)
        {
            width = atoi(fmt);
            while(*fmt > '0' && *fmt <= '9')
                fmt++;
            mode = MODE_LENGTH;
        }
        else if(mode == MODE_LENGTH)
        {
            if(*fmt == 'h' && *(fmt+1) == 'h')
                fmt++, arg.type = CHAR;
            else if(*fmt == 'h')
                arg.type = SHORT;
            else if(*fmt == 'l' && *(fmt+1) == 'l')
                fmt++, arg.type = LLONG;
            else if(*fmt == 'l')
                arg.type = LONG;
            else if(*fmt == 'L')
                arg.type = LDBL;
            else if(*fmt == 'j')
                arg.type = INTMAX;
            else if(*fmt == 'z')
                arg.type = SIZET;
            else if(*fmt == 't')
                arg.type = PTRDIFF;
            else
                fmt--, mode = MODE_CONVERSION;
            fmt++;
        }
        else if(mode == MODE_CONVERSION)
        {
            pop(&arg, &va);
            switch(*fmt)
            {
                case 'd':
                    bytes += fmt_int(arg, 0, padding, width);
                    break;
                case 'u':
                    // we already popped arg so we don't need length info
                    // fmt_int only cares about INT, LONG and LLONG
                    // everything else is treated as unsigned
                    arg.type = NIL;
                    bytes += fmt_int(arg, 0, padding, width);
                    break;
                case 'x':
                    bytes += fmt_int(arg, 1, padding, width);
                    break;
                case 's':
                    bytes += fmt_str(arg.p);
                    break;
                case 'p':
                    putchar('0'); putchar('x'); bytes += 2;
                    bytes += fmt_int(arg, 1, PADDING_ZERO, 8);
                default:
                    break;
            }

            arg.i = 0; arg.type = INT;
            padding = PADDING_SPACE; pos = POS_NONE;
            width = 0;
            fmt++;

            mode = MODE_SCAN;
        }
    }

    return bytes;
}

