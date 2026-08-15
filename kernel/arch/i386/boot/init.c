#include <stdio.h>
#include <stdint.h>

#include <panic.h>
#include <arch/i386/vga.h>
#include <arch/i386/mm/mm.h>
#include <drv/pckeyboard.h>

#include <multiboot2.h>

static inline void *mbt_next(struct multiboot_tag *tag)
{
    up p = (up)tag;
    p += tag->size + 7;
    p &= ~0b111;
    return (void *)p;
}

void multiboot2_init(void *mbi)
{
    u32 sz = *(u32*)mbi; // first field of *mbi is a u32 size
    void *p = mbi+8;

    while(p < (void*)mbi+sz)
    {
        struct multiboot_tag *tag = p;
        switch(tag->type)
        {
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                printf("meminfo\n");
                break;
            case MULTIBOOT_TAG_TYPE_MMAP:
                printf("mmap\n");
                break;
            case MULTIBOOT_TAG_TYPE_CMDLINE:
                printf("cmdline\n");
                break;
        }

        p = mbt_next(p);
    }
}

void i386_init(void *mbi, u32 magic)
{
    vga_init((void*)0xc03ff000, 14, 15);

    if(magic == MULTIBOOT2_BOOTLOADER_MAGIC)
        multiboot2_init(mbi);
    else
        panic("invalid magic num");
    panic("break");

    ps2_init();
    kb_init();
}

