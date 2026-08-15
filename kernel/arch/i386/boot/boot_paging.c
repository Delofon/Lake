#include <stdint.h>

#include <arch/i386/mm/mm.h>

#include "linker.h"
#include "../vga.h"

sect(".trampoline.text")
int init_kpd(u32 *kpd, u32 *kpt1)
{
    // map 4mb
    for(u32 i = 0;
            i < PG_DIR_SIZE;
            i++)
    {
        pde_t *pde = (void*)(kpt1+i);
        pde->base = i;
        pde->wr = 1;
        pde->p  = 1;
    }

    // map vga to the last available addr
    kpt1[PG_IDX_MAX] = 0xb8000 | PG_WR | PG_P | PG_PCD;

    // identity page trampoline
    kpd[0] = (up)(kpt1) | PG_WR | PG_P;

    // put lake into higher half
    u16 pdi = PG_DIR_IDX(usvlake);
    kpd[pdi] = (up)(kpt1) | PG_WR | PG_P;

    // recursion
    kpd[PG_IDX_MAX] = (up)kpd | PG_WR | PG_P;

    return 0;
}

