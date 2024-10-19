#include <stddef.h>

#include "string.h"

size_t strlen(const char *s)
{
    size_t len = 0;
    while(s[len]) len++;
    return len;
}

size_t strnlen(const char *s, size_t n)
{
    size_t len = 0;
    while(s[len] && len < n) len++;
    return len;
}

void *memset(void *s, uint8_t b, size_t n)
{
    for(size_t i = 0; i < n; i++) *((uint8_t*)s) = b;
    return s;
}

