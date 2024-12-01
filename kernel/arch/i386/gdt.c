#include <stdint.h>

#include "gdt.h"

void setup_gdt(uint64_t *gdtp, uint64_t *gdtp_end)
{
    encode_descriptor(gdtp,   0, 0, 0, 0);
    encode_descriptor(gdtp+1, 0, 0xfffff, 0x9a, 0x0c);
    encode_descriptor(gdtp+2, 0, 0xfffff, 0x92, 0x0c);
    encode_descriptor(gdtp+3, 0, 0xfffff, 0xfa, 0x0c);
    encode_descriptor(gdtp+4, 0, 0xfffff, 0xf2, 0x0c);
}

void encode_descriptor(uint64_t *descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    // TODO: Proper error handling (kernel panic)
    if(limit > 0xfffff)
        return;
    if(flags > 0b1111)
        return;

    uint64_t base_15    = base;         // 15 - 0  + 1 = 16
    uint64_t base_16_23 = base >> 16;   // 23 - 16 + 1 = 8
    uint64_t base_24_31 = base >> 24;   // 31 - 24 + 1 = 8

    uint64_t limit_15    = limit;       // 15 - 0  + 1 = 16
    uint64_t limit_16_19 = limit >> 16; // 19 - 16 + 1 = 4

    *descriptor |= limit_15;
    *descriptor |= base_15 << 16;

    *descriptor |= base_16_23 << 32;
    *descriptor |= (uint64_t)access << 40;
    *descriptor |= limit_16_19 << 48;
    *descriptor |= (uint64_t)flags << 52;
    *descriptor |= base_24_31 << 56;
}

