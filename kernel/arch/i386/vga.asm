VGA_WIDTH equ 80

section .data
breakmsg:
    db "break",0

section .text

extern panic

; non-working sheet

global vga_cursor_init
vga_cursor_init:
    push ebx

    mov ebx, [esp+8]   ; start_scanline
    mov ecx, [esp+12] ; end_scanline

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
    mov eax, [esp+4]   ; vga_x
    mov ecx, [esp+8] ; vga_y

    mov dx, VGA_WIDTH
    imul cx, dx
    add cx, ax
    inc cx

    push DWORD breakmsg
    call panic
    add esp, 4

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

