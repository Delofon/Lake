MPIC_COMMAND equ 0x20
MPIC_DATA    equ 0x21
SPIC_COMMAND equ 0xa0
SPIC_DATA    equ 0xa1

section .text
; basically zero documentation about what any of this does and where those codes come from?
; best hope is 8259 datasheet, but good luck learning how
; to easily control outdated chips in a reasonable time
global pic_init
pic_init:
    mov al, 0x11 ; start initialisation, expect 4 bytes

    out MPIC_COMMAND, al
    out SPIC_COMMAND, al

    mov al, 0 ; io sleep
    out 0x80, al

    mov al, 0x20 ; offset for IRQ 0 - 7
    out MPIC_DATA, al

    mov al, 0
    out 0x80, al

    mov al, 0x28 ; offset for IRQ 8 - 15
    out SPIC_DATA, al

    mov al, 0
    out 0x80, al

    mov al, 4 ; IRQ number for cascade from SPIC
    out MPIC_DATA, al

    mov al, 0
    out 0x80, al

    mov al, 2 ; cascade identity
    out SPIC_DATA, al

    mov al, 0
    out 0x80, al

    mov al, 1 ; 8086 mode
    out MPIC_DATA, al

    mov al, 0
    out 0x80, al

    mov al, 1
    out SPIC_DATA, al

    ret

global pic_eoi
pic_eoi:
    mov cl, BYTE [esp]

    mov al, 0x20

    cmp cl, 8
    jl set_mpic

    out SPIC_COMMAND, al
set_mpic:
    out MPIC_COMMAND, al

    ret

global pic_disable
pic_disable:
    mov al, 0xff
    out MPIC_DATA, al
    out SPIC_DATA, al

    ret

