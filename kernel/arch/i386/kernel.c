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

#include "gdt.h"

void protectedmode();

extern uint64_t *gdtp;
extern uint64_t *gdtp_end;

void pre_kmain()
{
    setup_gdt(gdtp, gdtp_end);
    protectedmode();
}

void kmain()
{
    vga_init();

    printf("Lake v2\n\n");

    printf("Hex test: %x\n", 0xdeadbeef);
}

