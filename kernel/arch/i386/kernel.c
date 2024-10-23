#ifdef __linux__
#error Wrong compiler (linux)
#endif // __linux__

#ifndef __i386__
#error Wrong compiler (no i386)
#endif // __i386__

#include <stdio.h>
#include <string.h>

#include <arch/i386/vga.h>

void kmain()
{
    vga_init();
    printf("Lake v0.0.1\nNewline test\n");
    vga_setcol(VGA_RED, VGA_BLACK);
    printf("Testier test\n");
    vga_setcol(VGA_LGRAY, VGA_BLACK);
    printf("printf test\n");
    printf("This should print 69: %d\n", 69);
    printf("Multiple %s", "strings?\n");

    char *s = "Bytes sanity check\n";
    int b = strlen(s);
    int printf_b = printf("%s", s);
    printf("strlen(s) = %d, printf_b = %d\n", b, printf_b);
}

