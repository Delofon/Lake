section .data
global gdtp
gdtp:
    dq 0
    dq 0
    dq 0
    dq 0
    dq 0
gdt_end:
gdt_size equ gdt_end - gdtp

gdtr:
    dw gdt_size - 1
    dd gdtp

section .text
global setgdt
setgdt:
    cli
    lgdt [gdtr]

    jmp 8:.farjump

.farjump:
    mov ax, 16
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret

