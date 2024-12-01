#include <stdio.h>
#include <stdint.h>

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

    printf("base limit access flags\n");
    printf("%x %x %x %x\n", base, limit, access, flags);

    descriptor[0] = (limit)      & 0xff;
    descriptor[1] = (limit >> 8) & 0xff;
    descriptor[2] = (base)       & 0xff;
    descriptor[3] = (base  >> 8) & 0xff;

    descriptor[4] = (base >> 16) & 0xff;
    descriptor[5] = (access);
    descriptor[6] = ((limit >> 12) & 0xf) | (flags & 0xf);
    descriptor[7] = (base >> 24) & 0xff;


    printf("0x%08x|%08x\n", *(uint32_t*)(descriptor+4), *(uint32_t*)descriptor);
    printf("==================\n");
}

int main()
{
    uint64_t null;
    uint64_t sd1;

    encode_descriptor((uint8_t*)&null, 0, 0, 0, 0);
    encode_descriptor((uint8_t*)&sd1, 0, 0xfffff, 0x9a, 0x0c);

    printf("\n");
    printf("null: 0x%016lx\n", null);
    printf("sd1:  0x%016lx\n", sd1);

    return 0;
}

