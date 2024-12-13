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
extern Keyboard_C

extern pic_eoi

global DoubleFault
DoubleFault:
    pusha

    push BYTE 0x8
    call panic_stub
    add esp, 1

    popa
    iret

global GeneralProtectionFault
GeneralProtectionFault:
    pusha

    push BYTE 0xd
    call panic_stub
    add esp, 1

    popa
    iret

global PIT
PIT:
    pusha
    call pic_eoi
    popa
    iret

global Keyboard
Keyboard:
    pusha

    call Keyboard_C

    call pic_eoi
    popa
    iret

global CMOS
CMOS:
    pusha
    call pic_eoi
    popa
    iret

