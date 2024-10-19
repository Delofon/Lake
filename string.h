#ifndef STRING_H_
#define STRING_H_

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);

void *memset(void *p, uint8_t b, size_t n);

#endif // STRING_H_

