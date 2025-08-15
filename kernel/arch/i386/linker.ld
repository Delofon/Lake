ENTRY(trampoline)

SECTIONS
{
    . = 2M;

    lake_lma_start = .;
    lake_vla_start = 0xc0000000;

    .multiboot ALIGN(4K) :
    {
        *(.multiboot)
    }

    .trampoline ALIGN(4K) :
    {
        *(.trampoline.data)
        *(.trampoline.text)
    }

    . += lake_vla_start;

    .text ALIGN(4K) :
    AT(ADDR(.text) - lake_vla_start)
    {
        *(.text)
    }

    .rodata ALIGN(4K) :
    AT(ADDR(.rodata) - lake_vla_start)
    {
        *(.rodata)
    }

    .data ALIGN(4K) :
    AT(ADDR(.data) - lake_vla_start)
    ALIGN(4K)
    {
        *(.data)
    }

    .bss ALIGN(4K) :
    AT(ADDR(.bss) - lake_vla_start)
    {
        *(COMMON)
        *(.bss)
    }

    lake_lma_end = . - lake_vla_start;
}

