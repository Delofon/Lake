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
#define PG_G   (1 << 8) // global

#define PG_DIR_MASK 0xffc00000
#define PG_TBL_MASK 0x003ff000
#define PG_PGE_MASK 0x00000fff

#define PG_DIR_IDX(x) (((x) & PG_DIR_MASK) >> 22)
#define PG_TBL_IDX(x) (((x) & PG_TBL_MASK) >> 12)

#endif

