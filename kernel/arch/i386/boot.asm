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

section .data
global gdtp
    dd 0x8badf00d
gdtp:
    dq 0
    dq 0
    dq 0
    dq 0
    dq 0
gdtp_end:
gdt_size equ gdtp_end - gdtp

gdtr:
    dw 0
    dd 0

section .text
global _start:function (_start.end - _start)

_start:
    mov esp, stack_space

    extern vga_init
    call vga_init

    push gdtp
    extern setup_gdt
    call setup_gdt
    add esp, 4

    call setgdt

    mov eax, cr0
    or al, 1
    mov cr0, eax

    jmp pmode

    jmp halt
.end:

global halt
halt:
    cli
.hang:
    hlt
    jmp .hang

setgdt:
    mov WORD  [gdtr],   gdt_size
    mov DWORD [gdtr+2], eax
    cli
    lgdt [gdtr]

    ret

pmode:
    mov ax, 8
    mov cs, ax
    mov ax, 16
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:halt

    extern kmain
    call kmain

    ret
.end:

