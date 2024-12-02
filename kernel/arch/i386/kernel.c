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

#include <arch/i386/vga.h>

void halt();

void kmain(uint8_t *gdtp)
{
    vga_init();

    printf("Lake v2\n\n");
}

