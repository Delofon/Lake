#ifndef MM_H_
#define MM_H_

#include <stddef.h>

void *alloc_ph_pg();
void *dealloc_ph_pg(void *ph_pg);

void *alloc_vm_pg();
void  dealloc_vm_pg(void *vm_pg);

#endif

