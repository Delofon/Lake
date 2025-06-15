section .text

global inb
inb:
    mov dx, WORD [esp+4]
    in al, dx

    ret

global outb
outb:
    mov dx, WORD [esp+4]
    mov al, BYTE [esp+8]

    out dx, al

    ret

global io_wait
io_wait:
    mov dx, 0x80
    mov al, 0
    out dx, al

    ret

