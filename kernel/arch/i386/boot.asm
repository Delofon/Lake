MBALIGN  equ 1 << 0
MEMINFO  equ 1 << 1
MBFLAGS  equ MBALIGN | MEMINFO
MAGIC    equ 0x1badb002
CHECKSUM equ -(MAGIC + MBFLAGS)

PROTECTION_ENABLE equ 1

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
extern printf
global _start:function (_start.end - _start)
_start:
    mov esp, stack_space

    extern vga_init
    call vga_init

    call enable_a20

    extern gdtp
    push gdtp
    extern setup_gdt
    call setup_gdt
    add esp, 4

    mov eax, cr0
    or  eax, PROTECTION_ENABLE
    mov cr0, eax

    extern setgdt
    call setgdt

    push gdtp
    extern kmain
    call kmain

    jmp halt
.end:

global halt
halt:
    cli
.hang:
    hlt
    jmp .hang

enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al

    ret

