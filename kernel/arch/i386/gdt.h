#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

void setup_gdt(uint64_t *gdtp, uint64_t *gdtp_end);
void encode_descriptor(uint64_t *descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

#endif // GDT_H_

