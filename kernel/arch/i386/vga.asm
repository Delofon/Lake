VGA_WIDTH equ 80

section .text

; non-working sheet

global vga_cursor_init
vga_cursor_init:
    push ebx

    mov edi, [esp]   ; start_scanline
    mov ecx, [esp+4] ; end_scanline

    mov al, 0x0a
    mov dx, 0x3d4
    out dx, al

    mov dx, 0x3d5
    in al, dx
    and al, 0xc0
    or al, bl
    out dx, al

    mov dx, 0x3d4
    mov al, 0x0b
    out dx, al

    mov dx, 0x3d5
    in al, dx
    and al, 0xe0
    or al, cl
    out dx, al

    pop ebx
    ret

global vga_cursor_move
vga_cursor_move:
    mov eax, [esp]   ; vga_x
    mov ecx, [esp+4] ; vga_y

    imul ecx, VGA_WIDTH
    add ecx, eax

    mov dx, 0x3d4
    mov al, 0x0f
    out dx, al

    mov dx, 0x3d5
    mov al, cl
    out dx, al

    mov dx, 0x3d4
    mov al, 0x0e
    out dx, al

    mov dx, 0x3d5
    mov al, ch
    out dx, al

    ret

