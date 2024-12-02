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
    printf("Lake v2\n\n");

    uint32_t *gdtw = (uint32_t *)gdtp;
    printf("gdtp:   0x%x|%x\n", gdtw[1], gdtw[0]);
    printf("gdtp+1: 0x%x|%x\n", gdtw[3], gdtw[2]);
    printf("gdtp+2: 0x%x|%x\n", gdtw[5], gdtw[4]);
    printf("gdtp+3: 0x%x|%x\n", gdtw[7], gdtw[6]);
    printf("gdtp+4: 0x%x|%x\n", gdtw[9], gdtw[8]);
}

