section .multiboot2

MB2_MAGIC    equ 0xe85250d6
MB2_ARCH     equ 0
MB2_SZ       equ MB2_END - MB2_BEGIN
MB2_CHECKSUM equ -(MB2_MAGIC + MB2_ARCH + MB2_SZ)

align 8
MB2_BEGIN:
    dd MB2_MAGIC
    dd MB2_ARCH
    dd MB2_SZ
    dd MB2_CHECKSUM

align 8 ; each tag is 8 byte aligned
t1.b:
    dw 1 ; request tag
    dw 0
    dd t1.e - t1.b
    dd 4 ; request low up mem
    dd 6 ; request mem maps
    dd 1 ; request cmdline
t1.e:

align 8
    dd 0
    dd 8
MB2_END:

section .trampoline.text

global trampoline:function
trampoline:
    ; linker.ld
    extern lake_vla_start

    mov esp, stack
    sub esp, lake_vla_start

    push eax
    push ebx

    lea edi, [kpt1]
    sub edi, lake_vla_start
    push edi

    lea ebx, [kpd]
    sub ebx, lake_vla_start
    push ebx

    extern init_kpd
    call init_kpd

    add esp, 8

    test eax, eax
    jz .ok

    cli
.notok:
    hlt
    jmp .notok

.ok:
    mov cr3, ebx

    WP equ 1 << 16 ; write protect
    PG equ 1 << 31 ; paging

    mov eax, cr0
    or  eax, WP | PG
    mov cr0, eax

    pop ebx
    pop eax

    jmp start

section .bss

global kpd
global kpt1

align 16
resb 16384
stack:
align 4096
kpd:
resd 1024
kpt1:
resd 1024

section .text

extern setup_gdt
extern setgdt

extern setup_idt
extern setidt

extern vga_init
extern pic_init
extern kmain
extern halt

extern gdtp
extern idtp

section .text

global start:function
start:
    ; get rid of identity
    mov dword [kpd], 0x0
    invlpg [0]

    mov esp, stack
    mov ebp, esp

    push eax
    push ebx

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

    ; do more i386 specific initialisation
    extern i386_init
    call i386_init

    ; booting finished, give control to the main kernel code
    call kmain

    jmp halt

