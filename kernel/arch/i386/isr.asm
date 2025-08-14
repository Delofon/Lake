section .text

extern panic_stub

; exceptions
extern DivisionError_C
extern Debug_C
extern NonMaskableInterrupt_C
extern Breakpoint_C
extern Overflow_C
extern BoundRangeExceeded_C
extern InvalidOpcode_C
extern DeviceNotAvailable_C
extern DoubleFault_C

extern InvalidTSS_C
extern SegmentNotPresent_C
extern StackSegmentFault_C
extern GeneralProtectionFault_C
extern PageFault_C

extern FloatingPoint_C
extern AlignmentCheck_C
extern MachineCheck_C

; IRQ
extern keyboard_irq

extern pic_eoi

global DoubleFault
DoubleFault:
    pusha

    push 0x8
    call panic_stub
    add esp, 4

    popa
    iret

global GeneralProtectionFault
GeneralProtectionFault:
    pusha

    push 0xd
    call panic_stub
    add esp, 4

    popa
    iret

global PageFault
PageFault:
    pusha

    push 0xe
    call panic_stub
    add esp, 4

    popa
    iret

global PIT
PIT:
    pusha

    push 0
    call pic_eoi
    add esp, 4

    popa
    iret

global Keyboard
Keyboard:
    pusha

    call keyboard_irq

    push 1
    call pic_eoi
    add esp, 4

    popa
    iret

global CMOS
CMOS:
    pusha

    push 8
    call pic_eoi
    add esp, 4

    popa
    iret

