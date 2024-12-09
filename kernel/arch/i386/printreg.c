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

    printf("eax = 0x%x ebx = 0x%x ecx = 0x%x edx = 0x%x\n", eax, ebx, ecx, edx);
    printf("edi = 0x%x esi = 0x%x\n", edi, esi);
    printf("ebp = 0x%x esp = 0x%x\n", ebp, esp);
}

