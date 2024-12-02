#include <stdio.h>
#include <stdint.h>

void encode_descriptor(uint8_t *descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

void setup_gdt(uint8_t *gdtp)
{
    encode_descriptor(gdtp,    0, 0, 0, 0);
    encode_descriptor(gdtp+8,  0, 0xaffff, 0x9a, 0x0c);
    encode_descriptor(gdtp+16, 0, 0xbffff, 0x92, 0x0c);
    encode_descriptor(gdtp+24, 0, 0xdffff, 0xfa, 0x0c);
    encode_descriptor(gdtp+32, 0, 0xeffff, 0xf2, 0x0c);
}

void encode_descriptor(uint8_t *descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
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

    descriptor[0] = (limit)      & 0xff;
    descriptor[1] = (limit >> 8) & 0xff;
    descriptor[2] = (base)       & 0xff;
    descriptor[3] = (base  >> 8) & 0xff;

    descriptor[4] = (base >> 16) & 0xff;
    descriptor[5] = (access);
    descriptor[6] = ((limit >> 16) & 0xf) | ((flags & 0xf) << 4);
    descriptor[7] = (base >> 24) & 0xff;
}

int main()
{
    uint64_t gdt[5];
    setup_gdt((uint8_t *)gdt);

    for(int64_t i = 0; i < 5; i++)
    {
        printf("gdt+%02ld: 0x%016lx\n", i*8, gdt[i]);
    }

    return 0;
}

