#if 0
#undef __linux__
#define __i386__
#endif

#ifdef __linux__
#error Wrong compiler (linux)
#endif // __linux__

#ifndef __i386__
#error Wrong compiler (no i386)
#endif // __i386__

#include "vga.h"

void kmain()
{
    vga_init();
    vga_puts("Lake v0.0.1");
}

