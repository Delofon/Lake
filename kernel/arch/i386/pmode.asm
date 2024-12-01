section .data
global gdtp
global gdtp_end
gdtp:
    resq 5
gdtp_end:

section .text
global protectedmode:function
protectedmode:
    cli
    lgdt [gdtp]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    ret

