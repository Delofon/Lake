#include <stdio.h>
#include <stdint.h>

#include "gdt.h"

void encode_descriptor(uint8_t *descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

void setup_gdt(uint8_t *gdtp)
{
    printf("0x%x\n", (uint32_t)gdtp);
    encode_descriptor(gdtp,    0, 0, 0, 0);
    encode_descriptor(gdtp+8,  0, 0xfffff, 0x9a, 0x0c); // kernel code
    encode_descriptor(gdtp+16, 0, 0xfffff, 0x92, 0x0c); // kernel data
    encode_descriptor(gdtp+24, 0, 0xfffff, 0xfa, 0x0c); // user   code
    encode_descriptor(gdtp+32, 0, 0xfffff, 0xf2, 0x0c); // user   data
}

void encode_descriptor(uint8_t *descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    // TODO: Proper error handling (kernel panic)
    if(limit > 0xfffff)
    {
        printf("Limit %d is greater than 0xfffff!\n", limit);
        return;
    }
    if(flags > 0xf)
    {
        printf("Flags %d are greater than 0xf!\n", flags);
        return;
    }

    printf("%x %x %x %x\n", base, limit, access, flags);

    descriptor[0] = (limit)      & 0xff;
    descriptor[1] = (limit >> 8) & 0xff;
    descriptor[2] = (base)       & 0xff;
    descriptor[3] = (base  >> 8) & 0xff;

    descriptor[4] = (base >> 16) & 0xff;
    descriptor[5] = (access);
    descriptor[6] = ((limit >> 12) & 0xf) | (flags & 0xf);
    descriptor[7] = (base >> 24) & 0xff;

    printf("0x%x|%x\n", *(uint32_t *)(descriptor+4), *(uint32_t *)descriptor);
    printf("==================\n");
}

