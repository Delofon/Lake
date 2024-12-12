section .text

extern test_interrupt_c

global test_interrupt
test_interrupt:
    pusha

    call   test_interrupt_c

    popa
    iret
.end:

