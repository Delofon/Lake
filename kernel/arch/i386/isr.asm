section .text
global test_interrupt
test_interrupt:
    pusha

    extern test_interrupt_c
    call   test_interrupt_c

    popa
    iret
.end:

