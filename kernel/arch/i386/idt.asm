section .bss
global idtp
idtp:
    resq 0x80
idt_end:
idt_size equ idt_end - idtp

section .data
idtr:
    dw idt_size - 1
    dd idtp

section .text
global setidt
setidt:
    cli
    lidt [idtr]

    ret

