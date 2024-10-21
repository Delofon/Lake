#include <stddef.h>

#include "stdlib.h"

int atoi(const char *s)
{
    int d = 0;
    _Bool ispos = 1;

    if(*s == '-')
    {
        ispos = 0;
        s++;
    }

    while(*s)
    {
        if(*s >= '0' && *s <= '9')
        {
            d = d*10 + (*s - '0');
        }
        else
            break;
        s++;
    }

    return d * (ispos ? 1 : -1);
}

