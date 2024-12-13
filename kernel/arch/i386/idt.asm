section .data

global idtp

idtp:
%rep 0x81
    dq 0
%endrep
idt_end:
idt_size equ idt_end - idtp

idtr:
    dw idt_size - 1
    dd idtp

section .text

global setidt
setidt:
    cli
    lidt [idtr]

    ret

