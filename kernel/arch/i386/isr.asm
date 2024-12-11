section .data
global test_interrupt
test_interrupt:
    dd test_interrupt_wrapper

section .text
test_interrupt_wrapper:
    pusha

    extern test_interrupt_c
    call   test_interrupt_c

    popa
    iret
.end:

