#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <panic.h>

#include <arch/i386/isr.h>

void halt();

void kmain(uint8_t *gdtp, uint32_t *idtp)
{
    printf("Lake v3\n\n");

    printf("gdtp: 0x%08x\n", gdtp);
    printf("idtp: 0x%08x\n", idtp);
    printf("0x%08x 0x%08x\n", idtp+0x80*2, idtp+0x80*2+1);
    printf("idtp+0x80: 0x%08x 0x%08x\n", idtp[0x80*2+1], idtp[0x80*2]);

    //for(;;);
    halt();
}

