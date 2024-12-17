section .bss
global regs
regs:
    resd 8

section .text
global savereg
savereg:
    mov [regs+0*4], eax
    mov [regs+1*4], ebx
    mov [regs+2*4], ecx
    mov [regs+3*4], edx

    mov [regs+4*4], edi
    mov [regs+5*4], esi

    mov [regs+6*4], ebp

    ; esp was also used for pushing eip when calling savereg
    ; similarly, it was also used when calling panic
    ; therefore, temporarily add 8 to esp
    add esp, 8
    mov [regs+7*4], esp
    sub esp, 8

    ret

