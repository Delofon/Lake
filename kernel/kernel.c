#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <panic.h>

#include <drv/keyboard.h>

#include <tty.h>

#include <arch/i386/isr.h>
#include <arch/i386/vga.h>

void halt();
void hang();

void kmain(uint8_t *gdtp, uint32_t *idtp)
{
    printf("Lake\n\n");

    while(1)
    {
        processkbscan();
        processtty();
        hang();
    }
}

