#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <panic.h>

#include <arch/i386/isr.h>

void halt();

void kmain(uint8_t *gdtp, uint32_t *idtp, uint32_t test_interrupt_arg)
{
    printf("Lake v3\n\n");

    printf("gdtp: 0x%x\n", gdtp);
    printf("idtp: 0x%x\n", idtp);
    printf("0x%x 0x%x\n", idtp+0x80*2, idtp+0x80*2+1);
    printf("idtp+0x80: 0x%x|%x\n", idtp[0x80*2+1], idtp[0x80*2]);
    printf("[kmain] test_interrupt_arg: 0x%x\n", test_interrupt_arg);
    printf("[kmain] test_interrupt:     0x%x\n", test_interrupt);

    halt();
}

