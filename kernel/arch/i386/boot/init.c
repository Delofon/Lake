#include <stdint.h>

#include <panic.h>
#include <arch/i386/vga.h>
#include <drv/pckeyboard.h>

#include <multiboot2.h>

void multiboot2_init(void *mbi, uint32_t magic)
{
}

void i386_init(void *mbi, uint32_t magic)
{
    vga_init((void*)0xc03ff000, 14, 15);

    if(magic == MULTIBOOT2_BOOTLOADER_MAGIC)
        multiboot2_init(mbi, magic);
    else
        panic("invalid magic num");

    ps2_init();
    kb_init();
}

