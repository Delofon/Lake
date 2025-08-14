#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "../mm.h"

// linker.ld
uint32_t lake_vla_start = 0xc0000000;
uint32_t trampoline_start = 0x00201000;
uint32_t trampoline_end = 0x00201137;

void init_kpd(uint32_t *kpd, uint32_t *kpt1)
{
    // identity page trampoline
    kpd[0] = (uint32_t)(kpt1) | PG_WR | PG_P;

    for(uint32_t phys_pg = (uint32_t)trampoline_start;
                 phys_pg < (uint32_t)trampoline_end;
                 phys_pg += 4096)
    {
        uint16_t pti = (phys_pg & 0x003ff000) >> 12;
        kpt1[pti] = (phys_pg) | PG_WR | PG_P;
    }

    // put lake into higher half
}

int main()
{
    uint32_t *kpd  = (uint32_t *)mmap((void *)0x00207000, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    uint32_t *kpt1 = (uint32_t *)mmap((void *)0x00208000, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    init_kpd(kpd, kpt1);

    return 0;
}

