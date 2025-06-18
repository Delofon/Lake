MBALIGN  equ 1 << 0
MEMINFO  equ 1 << 1
MBFLAGS  equ MBALIGN | MEMINFO
MAGIC    equ 0x1badb002
CHECKSUM equ -(MAGIC + MBFLAGS)

PROTECTION_ENABLE equ 1

section .multiboot
align 4
    dd MAGIC
    dd MBFLAGS
    dd CHECKSUM

section .bss
align 16
resb 16384
stack_space:

section .text

extern gdtp
extern idtp

extern vga_init
extern setup_gdt
extern setgdt
extern setup_idt
extern setidt
extern pic_init
extern kmain

global _start:function (_start.end - _start)
_start:
    mov esp, stack_space
    mov ebp, esp

    call vga_init

    call enable_a20

    ; fill global descriptor table with flat segments
    push gdtp
    call setup_gdt
    add esp, 4

    ; turn on pmode
    mov eax, cr0
    or  eax, PROTECTION_ENABLE
    mov cr0, eax

    ; set gdtr register
    call setgdt

    ; fill interrupt table
    push idtp
    call setup_idt
    add esp, 4

    ; set idtr register
    call setidt

    ; initialise PIC chips with required offsets
    call pic_init

    ; we're ready for interrupts,
    ; setting gdt and idt required clearing interrupt flag so reset it
    sti

    ; booting finished, give control to the main kernel code
    call kmain

    jmp halt
.end:

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

enable_a20:
    mov dx, 0x92
    in al, dx
    or al, 2
    out dx, al

    ret

