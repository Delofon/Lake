#ifndef IO_H_
#define IO_H_

#include <stdint.h>

// TODO: ensure this is cpu agnostic
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
void io_wait();

#endif

