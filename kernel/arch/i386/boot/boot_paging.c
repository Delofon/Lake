#include <stdint.h>

#include <arch/i386/mm/mm.h>

// linker.ld
extern const void lake_lma_start;
extern const void lake_lma_end;
extern const void lake_vla_start;

__attribute__((section(".trampoline.text")))
int init_kpd(uint32_t *kpd, uint32_t *kpt1)
{
    // map lake
    for(uint32_t pg = (uint32_t)&lake_lma_start;
                 pg < (uint32_t)&lake_lma_end;
                 pg += 4096)
    {
        uint16_t pti = PG_TBL_IDX(pg);
        if(pti > 1023) return 1;

        kpt1[pti] = (pg) | PG_WR | PG_P;
    }

    // map vga to the last available addr
    kpt1[0x3ff] = 0xb8000 | PG_WR | PG_P | PG_PCD;

    // identity page trampoline
    kpd[0] = (uint32_t)(kpt1) | PG_WR | PG_P;

    // put lake into higher half

    uint16_t pdi = PG_DIR_IDX((uint32_t)&lake_vla_start);
    kpd[pdi] = (uint32_t)(kpt1) | PG_WR | PG_P;

    return 0;
}

