section .data
global gdtp
pre_gdtp:
    dd 0x8badf00d
gdtp:
    resq 5
gdtp_end:
gdt_size: equ gdtp_end - gdtp

gdtr:
    resw 1
    resd 1

section .text
global protectedmode:function
protectedmode:
    cli

    mov WORD  [gdtr],   gdt_size
    mov DWORD [gdtr+2], gdtp
    lgdt [gdtp]

    mov eax, cr0
    or al, 1
    mov cr0, eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret

