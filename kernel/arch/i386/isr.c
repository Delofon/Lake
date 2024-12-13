#include <stdio.h>

#include <panic.h>

void DoubleFault_C()
{
    panic("double fault");
}

void test_interrupt_c()
{
    printf("Hello from interrupt!\n");
}

