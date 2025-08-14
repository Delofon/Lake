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
resb 64 ; trampoline does not need large stack
trampoline_stack:

section .trampoline.text

; TODO: more sophisticated a20
enable_a20:
    mov dx, 0x92
    in al, dx
    or al, 2
    out dx, al

    ret

PE equ 1 << 0
WP equ 1 << 16
PG equ 1 << 31

global trampoline:function
trampoline:
    mov esp, trampoline_stack
    mov ebp, esp

    ; should probably be done by bootloader and not the kernel?
    ; we are already in pmode by the time we're in the kernel
    ; thanks to grub so this shouldn't be necessary
    ; (ideally paging setup would also be moved to bootloader...)
    ;call enable_a20

    ; linker.ld
    extern lake_vla_start

    lea edi, [kpt1]
    sub edi, lake_vla_start
    push edi

    lea ebx, [kpd]
    sub ebx, lake_vla_start
    push ebx

    extern init_kpd
    call init_kpd

    add esp, 8

    mov cr3, ebx

    ; turn on paging
    mov eax, cr0
    or  eax, PE | WP | PG
    mov cr0, eax

    jmp landpad

section .text
landpad:
    mov dword [kpd], 0x0

    mov eax, cr3
    mov cr3, eax

    jmp _start

section .bss

global kpd
global kpt1

align 4096
kpd:
resd 1024
kpt1:
resd 1024
; looks like stack may overflow into page tables... oops
align 16
resb 16384
stack:

section .text

extern setup_gdt
extern setgdt

extern setup_idt
extern setidt

extern vga_init
extern pic_init
extern kmain

extern gdtp
extern idtp

global _start:function
_start:
    mov esp, stack
    mov ebp, esp

    call vga_init

    ; fill global descriptor table with flat segments
    push gdtp
    call setup_gdt
    add esp, 4

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


