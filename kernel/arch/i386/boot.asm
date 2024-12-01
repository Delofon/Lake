MBALIGN  equ 1 << 0
MEMINFO  equ 1 << 1
MBFLAGS  equ MBALIGN | MEMINFO
MAGIC    equ 0x1badb002
CHECKSUM equ -(MAGIC + MBFLAGS)

section .multiboot
align 4
    dd MAGIC
    dd MBFLAGS
    dd CHECKSUM

section .bss
align 16
resb 16384
stack_space:

section .text
global _start:function (_start.end - _start)

_start:
    mov esp, stack_space

    extern gdtp
    extern gdtp_end
    push gdtp_end
    push gdtp

    extern pre_kmain
    call kmain
    add esp, 8

    extern kmain
    call kmain
    cli
.hang:
    hlt
    jmp .hang
.end:

