#ifndef LINKER_H_
#define LINKER_H_

// Exposed by linker.ld

extern const u0 lake_lma_start;
extern const u0 lake_lma_end;
// For some (now unknown) reason,
// I (erroneously) type VLA instead of VMA.
extern const u0 lake_vla_start;
extern const u0 lake_vla_end;
extern const u0 sbss;
extern const u0 ebss;
extern const u0 strampoline;
extern const u0 etrampoline;

#define svlake      (&lake_vla_start)
#define evlake      (&lake_vla_end  )
#define sllake      (&lake_lma_start)
#define ellake      (&lake_lma_end  )
#define svbss       (&sbss          )
#define evbss       (&ebss          )
#define strampoline (&strampoline   )
#define etrampoline (&etrampoline   )

#define usvlake      ((up)&lake_vla_start)
#define uevlake      ((up)&lake_vla_end  )
#define usllake      ((up)&lake_lma_start)
#define uellake      ((up)&lake_lma_end  )
#define usvbss       ((up)&sbss          )
#define uevbss       ((up)&ebss          )
#define ustrampoline ((up)&strampoline   )
#define uetrampoline ((up)&etrampoline   )

#endif

