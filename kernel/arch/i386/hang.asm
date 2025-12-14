section .text

; halt - turn off operations
; hang - stop eating cpu cycles until interrupt
global halt
halt:
    cli
.hlt:
    hlt
    jmp .hlt

global hang
hang:
    hlt
    ret

