#include <stdio.h>
#include <stdint.h>

#include <panic.h>

#include "isr.h"

void encode_idt(uint64_t *idtp, uint32_t offset, uint16_t segment, uint8_t gate, uint8_t dpl, uint8_t present)
{
    if(gate > 0xf)
    {
        printf("Invalid gate value: 0x%08x\n", gate);
        printf("0x%08x 0x%08x %u %u %u %u\n", (uint32_t)idtp, offset, segment, gate, dpl, present);
        panic("bad interrupt descriptor");
    }

    if(dpl > 0b11)
    {
        printf("Invalid dpl value: 0x%08x\n", dpl);
        printf("0x%08x 0x%08x %u %u %u %u\n", (uint32_t)idtp, offset, segment, gate, dpl, present);
        panic("bad interrupt descriptor");
    }

    if(present > 1)
    {
        printf("Invalid present value: 0x%08x\n", dpl);
        printf("0x%08x 0x%08x %u %u %u %u\n", (uint32_t)idtp, offset, segment, gate, dpl, present);
        panic("bad interrupt descriptor");
    }

    uint8_t *descriptor = (void *)idtp;

    uint16_t offset_1 = offset & 0xffff;
    uint16_t offset_2 = (offset >> 16) & 0xffff;

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
    //         idtp+offset   ptr to handler   GDTseg gate dpl p
    encode_idt(idtp+0x8, (uint32_t)DoubleFault, 8, 0b1111, 0, 1);
    encode_idt(idtp+0xd, (uint32_t)GeneralProtectionFault, 8, 0b1111, 0, 1);
    encode_idt(idtp+0xe, (uint32_t)PageFault, 8, 0b1111, 0, 1);

    encode_idt(idtp+(0 + 0x20), (uint32_t)PIT, 8, 0b1110, 0, 1);
    encode_idt(idtp+(1 + 0x20), (uint32_t)Keyboard, 8, 0b1110, 0, 1);
    encode_idt(idtp+(8 + 0x28 - 8), (uint32_t)CMOS, 8, 0b1110, 0, 1);
}

