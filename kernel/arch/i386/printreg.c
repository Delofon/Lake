#include <stdio.h>

void printreg()
{
    register int eax asm("eax");
    register int ebx asm("ebx");
    register int ecx asm("ecx");
    register int edx asm("edx");
    register int edi asm("edi");
    register int esi asm("esi");

    register int ebp asm("ebp");
    register int esp asm("esp");

    printf("eax = 0x%08x ebx = 0x%08x ecx = 0x%08x edx = 0x%08x\n", eax, ebx, ecx, edx);
    printf("edi = 0x%08x esi = 0x%08x\n", edi, esi);
    printf("ebp = 0x%08x esp = 0x%08x\n", ebp, esp);
}

