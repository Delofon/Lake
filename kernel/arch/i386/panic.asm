section .data
panicmsg:
    db 10,"kernel panic: %s",10,0

section .text

extern savereg
extern printreg
extern printf
extern halt

global panic
panic:
    call savereg

    push DWORD [esp+4]
    push DWORD panicmsg
    call printf
    add esp, 8

    call printreg

    jmp halt

