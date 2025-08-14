#include <stdint.h>

#include "mm.h"

// linker.ld
extern void lake_lma_start;
extern void lake_lma_end;
extern void lake_vla_start;
extern void trampoline_start;
extern void trampoline_end;

__attribute__((section(".trampoline.text")))
void init_kpd(uint32_t *kpd, uint32_t *kpt1)
{
    // map lake
    for(uint32_t pg = (uint32_t)&lake_lma_start;
                 pg < (uint32_t)&lake_lma_end;
                 pg += 4096)
    {
        uint16_t pti = (pg & 0x003ff000) >> 12;
        while(pti > 1023) asm volatile("hlt");

        kpt1[pti] = (pg) | PG_WR | PG_P;
    }

    // map vga to the last available addr
    kpt1[0x3ff] = 0xb8000 | PG_WR | PG_P;

    // identity page trampoline
    kpd[0] = (uint32_t)(kpt1) | PG_WR | PG_P;

    // put lake into higher half

    uint16_t pdi = ((uint32_t)&lake_vla_start & 0xffc00000) >> 22;
    kpd[pdi] = (uint32_t)(kpt1) | PG_WR | PG_P;
}

