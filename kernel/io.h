#ifndef IO_H_
#define IO_H_

#include <stdint.h>

// TODO: ensure this is cpu agnostic
void outb(uint16_t port, uint8_t data);
void io_wait();

#endif

