section .text

extern DoubleFault_C
extern test_interrupt_c

extern pic_eoi

global PIT
PIT:
    call pic_eoi
    iret

global CMOS
CMOS:
    call pic_eoi
    iret

global DoubleFault
DoubleFault:
    pusha

    call DoubleFault_C

    popa
    iret

global test_interrupt
test_interrupt:
    pusha

    call   test_interrupt_c

    popa
    iret
.end:

