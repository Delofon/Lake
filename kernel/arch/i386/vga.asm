VGA_WIDTH equ 80

section .text

; non-working sheet

global vga_cursor_init
vga_cursor_init:
    mov edx, [esp]   ; start_scanline
    mov ecx, [esp+4] ; end_scanline

    mov al, 0x0a
    out 0x3d4, al

    in al, 0x3d5
    and al, 0xc0
    or al, dl
    out 0x3d5, al

    in al, 0x0b
    out 0x3d4, al

    in al, 0x3d5
    and al, 0xe0
    or al, cl
    out 0x3d5, al

    ret

global vga_cursor_move
vga_cursor_move:
    mov eax, [esp]   ; vga_x
    mov ecx, [esp+4] ; vga_y

    imul ecx, VGA_WIDTH
    add ecx, eax

    mov al, 0x0f
    out 0x3d4, al

    mov al, cl
    out 0x3d5, al

    mov al, 0x0e
    out 0x3d4, al

    mov al, ch
    out 0x3d5, al

    ret

