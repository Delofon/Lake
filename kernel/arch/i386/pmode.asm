section .data
global gdtp
global gdtp_end
pre_gdtp:
    dd 0x8badf00d
gdtp:
    resq 5

section .text
global protectedmode:function
protectedmode:
    cli
    lgdt [gdtp]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    ret

