#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include <arch/i386/vga.h>
#include <drv/pckeyboard.h>

#include <panic.h>
#include <tty.h>

void halt();
void hang();

void kmain()
{
    printf("Lake\n\n");

    while(1)
    {
        processkbscan();
        processtty();
        hang();
    }
}

