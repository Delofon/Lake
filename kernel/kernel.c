#ifdef __linux__
#error Wrong compiler (linux)
#endif // __linux__

#ifndef __i386__
#error Wrong compiler (no i386)
#endif // __i386__

// TODO: remove
#include "arch/i386/vga.h"

void kmain()
{
    vga_init();
    vga_puts("Lake v0.0.1\nNewline test\n");
    vga_setcol(VGA_RED, VGA_BLACK);
    vga_puts("Testier test\n");
}

