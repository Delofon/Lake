#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <panic.h>

#include <arch/i386/isr.h>
#include <arch/i386/vga.h>

void hang();

void kmain(uint8_t *gdtp, uint32_t *idtp)
{
    printf("Lake v3\n\n");

    printf("%s", "cursor test\n");
    vga_cursor_move(3, 0);

    hang();
}

