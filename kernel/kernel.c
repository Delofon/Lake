#ifdef __linux__
#error Wrong compiler (linux)
#endif // __linux__

#ifndef __i386__
#error Wrong compiler (no i386)
#endif // __i386__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <panic.h>

void halt();

void kmain(uint8_t *gdtp)
{
    printf("Lake v2\n\n");

    panic("Panic test");
}

