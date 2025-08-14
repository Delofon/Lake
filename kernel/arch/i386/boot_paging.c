#include <stdint.h>

#include "mm.h"

// linker.ld
extern void lake_lma_start;
extern void lake_vla_start;
extern void trampoline_start;
extern void trampoline_end;

__attribute__((section(".trampoline.text")))
void init_kpd(uint32_t *kpd, uint32_t *kpt1)
{
    // identity page trampoline
    kpd[0] = (uint32_t)(kpt1) | PG_WR | PG_P;

    for(uint32_t phys_pg = (uint32_t)&trampoline_start;
                 phys_pg < (uint32_t)&trampoline_end;
                 phys_pg += 4096)
    {
        uint16_t pti = (phys_pg & 0x003ff000) >> 12;
        kpt1[pti] = (phys_pg) | PG_WR | PG_P;
    }

    // put lake into higher half
}

