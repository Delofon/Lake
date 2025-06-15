#include <stdio.h>
#include <stdint.h>

#include <panic.h>

void encode_gdt(uint8_t *descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    if(limit > 0xfffff)
    {
        printf("Limit %d is greater than 0xfffff!\n", limit);
        printf("%x %x %x %x %x\n", descriptor, base, limit, access, flags);
        panic("bad gdt descriptor");
    }
    if(flags > 0xf)
    {
        printf("Flags %d are greater than 0xf!\n", flags);
        printf("%x %x %x %x %x\n", descriptor, base, limit, access, flags);
        panic("bad gdt descriptor");
    }

    descriptor[0] = (limit)      & 0xff;
    descriptor[1] = (limit >> 8) & 0xff;
    descriptor[2] = (base)       & 0xff;
    descriptor[3] = (base  >> 8) & 0xff;

    descriptor[4] = (base >> 16) & 0xff;
    descriptor[5] = (access);
    descriptor[6] = ((limit >> 16) & 0xf) | ((flags & 0xf) << 4);
    descriptor[7] = (base >> 24) & 0xff;
}

void setup_gdt(uint8_t *gdtp)
{
    encode_gdt(gdtp,    0, 0, 0, 0);
    encode_gdt(gdtp+8,  0, 0xfffff, 0x9a, 0x0c); // kernel code
    encode_gdt(gdtp+16, 0, 0xfffff, 0x92, 0x0c); // kernel data
    encode_gdt(gdtp+24, 0, 0xfffff, 0xfa, 0x0c); // user   code
    encode_gdt(gdtp+32, 0, 0xfffff, 0xf2, 0x0c); // user   data
}

