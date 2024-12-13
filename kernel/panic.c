#include <stdio.h>

#include "panic.h"

// TODO: Move this to some header file?
void halt();

void panic(const char *msg)
{
    printf("\nkernel panic: %s\n", msg);
    printreg();
    halt();
}

