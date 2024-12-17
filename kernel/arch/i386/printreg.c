#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

extern uint32_t regs[8];

void printreg()
{
    uint32_t eax = regs[0];
    uint32_t ebx = regs[1];
    uint32_t ecx = regs[2];
    uint32_t edx = regs[3];
    uint32_t edi = regs[4];
    uint32_t esi = regs[5];

    uint32_t ebp = regs[6];
    uint32_t esp = regs[7];

    printf("eax = 0x%08x ebx = 0x%08x ecx = 0x%08x edx = 0x%08x\n", eax, ebx, ecx, edx);
    printf("edi = 0x%08x esi = 0x%08x\n", edi, esi);
    printf("ebp = 0x%08x esp = 0x%08x\n", ebp, esp);
}

