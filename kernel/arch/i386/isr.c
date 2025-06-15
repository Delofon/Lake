#include <stdio.h>
#include <stdint.h>

#include <panic.h>
#include <io.h>

const char *exception_msg[] =
{
    "division error",
    "debug",
    "NMI",
    "breakpoint",
    "overflow",
    "bound range exceeded",
    "invalid opcode",
    "device not available",
    "double fault",
    "N/A",
    "invalid TSS",
    "segment not present",
    "stack segment fault",
    "general protection fault",
    "page fault",
    "N/A",
    "floating point exception",
    "alignment check",
    "machine check",
    0
};

void panic_stub(uint32_t exception_num)
{
    panic(exception_msg[exception_num]);
}

// keyboard.c
extern uint8_t scancode;

// TODO: Maybe move to drv/keyboard.c?
void Keyboard_C()
{
    uint8_t status = inb(0x64);
    io_wait();

    if(status & 0x1)
    {
        scancode = inb(0x60);
        io_wait();
    }
}

