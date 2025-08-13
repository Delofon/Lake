section .multiboot

MAGIC    equ 0x1badb002

MBALIGN  equ 1 << 0
MEMINFO  equ 1 << 1
MBFLAGS  equ MBALIGN | MEMINFO

CHECKSUM equ -(MAGIC + MBFLAGS)

align 4
    dd MAGIC
    dd MBFLAGS
    dd CHECKSUM

section .trampoline.data

align 16
resb 16384
trampoline_stack:

section .trampoline.text

extern gdtp

extern setup_gdt
extern setgdt

PE equ 1 << 0
PG equ 1 << 31

global trampoline:function
trampoline:
    mov esp, trampoline_stack
    mov ebp, esp

    call enable_a20

    ; fill global descriptor table with flat segments
    push gdtp
    call setup_gdt
    add esp, 4

    ; set gdtr register
    call setgdt

    ; turn on pmode
    mov eax, cr0
    or  eax, PE
    mov cr0, eax

    ; TODO: identity page trampoline
    ; TODO: create basic page directory for higher half
    ; TODO: properly jump to _start vma
    hlt

    jmp _start

; TODO: more sophisticated a20
enable_a20:
    mov dx, 0x92
    in al, dx
    or al, 2
    out dx, al

    ret

section .text

extern vga_init
extern setup_idt
extern setidt
extern pic_init
extern kmain

extern idtp

global _start:function
_start:
    call vga_init

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


