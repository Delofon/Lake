ENTRY(trampoline)

SECTIONS
{
    . = 2M;

    lake_start = .;

    .multiboot BLOCK(4K) :
    ALIGN(4K)
    {
        *(.multiboot)
    }

    .trampoline BLOCK(4K) :
    ALIGN(4K)
    {
        *(.trampoline.data)
        *(.trampoline.text)

        /* A workaround to have setgdt available
         * in trampoline code.
         */
        *setgdt.c.o(.text)
    }

    offset = 0xc0000000;
    . += offset;

    .text BLOCK(4K) :
    AT(ADDR(.text) - offset)
    ALIGN(4K)
    {
        *(.text)
    }

    .rodata BLOCK(4K) :
    AT(ADDR(.rodata) - offset)
    ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) :
    AT(ADDR(.data) - offset)
    ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) :
    AT(ADDR(.bss) - offset)
    ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    lake_end = .;
}

