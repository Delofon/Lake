#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

extern u32 regs[9];

void printreg()
{
    u32 eax = regs[0];
    u32 ebx = regs[1];
    u32 ecx = regs[2];
    u32 edx = regs[3];
    u32 edi = regs[4];
    u32 esi = regs[5];

    u32 ebp = regs[6];
    u32 esp = regs[7];

    u32 cr2 = regs[8];

    printf("eax = 0x%08x ebx = 0x%08x ecx = 0x%08x edx = 0x%08x\n", eax, ebx, ecx, edx);
    printf("edi = 0x%08x esi = 0x%08x\n", edi, esi);
    printf("ebp = 0x%08x esp = 0x%08x\n", ebp, esp);
    printf("cr2 = 0x%08x\n", cr2);
}

