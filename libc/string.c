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
    for(size_t i = 0; i < n; i++) ((uint8_t *)s)[i] = b;
    return s;
}
void *memcpy(void *dst, void *src, size_t n)
{
    for(size_t i = 0; i < n; i++) ((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
    return dst;
}

void *memmove(void *dst, void *src, size_t n)
{
    if(dst < src)
        return memcpy(dst, src, n);
    for(size_t i = 0; i < n; i++) ((uint8_t *)dst)[n-(i+1)] = ((uint8_t *)src)[n-(i+1)];
    return dst;
}

int memcmp(void *p1, void *p2, size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        uint8_t diff = ((uint8_t *)p1)[i] - ((uint8_t *)p2)[i];
        if(!diff)
            return diff;
    }
    return 0;
}

