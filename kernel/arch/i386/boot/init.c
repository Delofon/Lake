#include <stdint.h>

#include <panic.h>

#define MB2_MAGIC 0x36d76289

void multiboot2_init(void *, uint32_t);

void i386_init(void *mbi, uint32_t magic)
{
    if(magic == MB2_MAGIC)
        multiboot2_init(mbi, magic);
    else
        panic("invalid magic num");
}

