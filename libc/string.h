#ifndef STRING_H_
#define STRING_H_

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);

void *memset(void *p, uint8_t b, size_t n);
void *memcpy(void *dst, void *src, size_t n);
void *memmove(void *dst, void *src, size_t n);
int memcmp(void *p1, void *p2, size_t n);

#endif // STRING_H_

