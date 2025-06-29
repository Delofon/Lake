#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include <arch/i386/isr.h>
#include <arch/i386/vga.h>
#include <drv/pckeyboard.h>

#include <panic.h>
#include <tty.h>

void halt();
void hang();

void kmain()
{
#if 0
    // test display
    const char *b64 = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_";
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 80; j++)
        {
            putchar(b64[(j+i)%64]);
        }
    }
#else
    printf("Lake\n\n");
#endif

    ps2_init();
    kb_init();

    while(1)
    {
        processkbscan();
        processtty();
        hang();
    }
}

