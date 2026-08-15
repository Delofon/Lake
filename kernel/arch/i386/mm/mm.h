#ifndef i386_MM_H_
#define i386_MM_H_

// Page flags
#define PG_P   (1 << 0) // present
#define PG_WR  (1 << 1) // writable
#define PG_USR (1 << 2) // userspace
#define PG_PWT (1 << 3) // writethrough
#define PG_PCD (1 << 4) // cache disable
#define PG_A   (1 << 5) // accessed
#define PG_D   (1 << 6) // dirty
#define PG_SZ  (1 << 7) // hugepage
#define PG_PAT (1 << 7) // attribute table
#define PG_G   (1 << 8) // global

#define PG_DIR_MASK 0xffc00000
#define PG_TBL_MASK 0x003ff000

#define PG_DIR_IDX(x) (((x) & PG_DIR_MASK) >> 22)
#define PG_TBL_IDX(x) (((x) & PG_TBL_MASK) >> 12)

#define PG_SIZE 4096

typedef struct
{
    u8 p   : 1;
    u8 wr  : 1;
    u8 us  : 1;
    u8 wt  : 1;
    u8 pcd : 1;
    u8 a   : 1;
    u8 d   : 1;
    u8 sz  : 1;
    u8 g   : 1;
} ptflags_t;
typedef struct
{
    u8 p   : 1;
    u8 wr  : 1;
    u8 us  : 1;
    u8 wt  : 1;
    u8 pcd : 1;
    u8 a   : 1;
    u8 avl : 1;
    u8 sz  : 1;
} pdflags_t;

typedef union
{
    u32 i;
    struct
    {
        u8 p   : 1;
        u8 wr  : 1;
        u8 us  : 1;
        u8 wt  : 1;
        u8 pcd : 1;
        u8 a   : 1;
        u8 d   : 1;
        u8 sz  : 1;
        u8 g   : 1;

        u8  avl  : 3;
        u32 base : 20;
    };
} pte_t;
ct_ass(sizeof(pte_t) == 4, "Invalid pg_t size");
typedef union
{
    u32 i;
    struct
    {
        u8 p   : 1;
        u8 wr  : 1;
        u8 us  : 1;
        u8 wt  : 1;
        u8 pcd : 1;
        u8 a   : 1;
        u8 avl2: 1;
        u8 sz  : 1;

        u8  avl1 : 4;
        u32 base : 20;
    };
} pde_t;
ct_ass(sizeof(pde_t) == 4, "Invalid pt_t size");

#define PG_IDX_MAX  0x3ff
#define PG_DIR_SIZE 0x400

extern up lomem;
extern up himem;

void  pmm_init();
void *pmm_alloc();
void  pmm_dealloc(void *p);

void  vmm_init();
void *vmm_alloc(pde_t *pd);
void  vmm_dealloc(pde_t *pd);

#endif

