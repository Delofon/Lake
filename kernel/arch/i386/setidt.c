#include <stdio.h>
#include <stdint.h>

#include "isr.h"

void encode_idt(uint64_t *idtp, uint32_t offset, uint16_t segment, uint8_t gate, uint8_t dpl, uint8_t present)
{
    if(gate > 0xf)
    {
        printf("Invalid gate value: 0x%08x\n", gate);
        printf("%08x %08x %u %u %u %u\n", (uint32_t)idtp, offset, segment, gate, dpl, present);
        return;
    }

    if(dpl > 0b11)
    {
        printf("Invalid dpl value: 0x%08x\n", dpl);
        printf("%08x %08x %u %u %u %u\n", (uint32_t)idtp, offset, segment, gate, dpl, present);
        return;
    }

    if(present > 1)
    {
        printf("Invalid present value: 0x%08x\n", dpl);
        printf("%08x %08x %u %u %u %u\n", (uint32_t)idtp, offset, segment, gate, dpl, present);
        return;
    }
    printf("%x %x %x %x %x %x\n", (uint32_t)idtp, offset, segment, gate, dpl, present);
    uint8_t *descriptor = (void *)idtp;

    uint16_t offset_1 = offset & 0xffff;
    uint16_t offset_2 = (offset >> 16) & 0xffff;

    printf("Setting at address: 0x%08x\n", idtp);
    printf("or:                 0x%08x\n", descriptor);
    printf("Second dword:       0x%08x\n", descriptor+4);

    descriptor[0] = (offset_1)      & 0xff;
    descriptor[1] = (offset_1 >> 8) & 0xff;
    descriptor[2] = (segment)       & 0xff;
    descriptor[3] = (segment  >> 8) & 0xff;

    descriptor[4]  = 0;
    descriptor[5]  = gate;
    descriptor[5] |= dpl     << 5;
    descriptor[5] |= present << 7;
    descriptor[6]  = (offset_2)      & 0xff;
    descriptor[7]  = (offset_2 >> 8) & 0xff;
}

void setup_idt(uint64_t *idtp)
{
    printf("[setup_idt] test_interrupt: 0x%08x\n", test_interrupt);
    encode_idt(idtp+0x80, (uint32_t)test_interrupt, 16, 0b1110, 0, 1);
}

