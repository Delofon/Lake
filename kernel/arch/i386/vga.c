#include <stdint.h>
#include <string.h>

#include "vga.h"

size_t vga_x;
size_t vga_y;

uint8_t vga_color;
uint16_t *vga_buf;

uint8_t vga_init()
{
    vga_x = 0;
    vga_y = 0;

    vga_setcol(VGA_LGRAY, VGA_BLACK);
    vga_buf = (uint16_t*)0xb8000;

    for(int i = 0; i < VGA_SIZE; i++)
    {
        vga_buf[i] = vga_color << 8 | ' ';
    }

    return 0;
}

void vga_putchar(char c)
{
    if(c == '\n')
    {
        vga_linefeed();
        return;
    }

    vga_buf[vga_coordtoi()] = vga_color << 8 | c;
    if(++vga_x >= VGA_WIDTH)
        vga_linefeed();
}

void vga_puts(char *s)
{
    while(*s) vga_putchar(*(s++));
}

void vga_scroll()
{
    memmove(vga_buf, vga_buf+VGA_WIDTH, VGA_WIDTH*(VGA_HEIGHT-1));
}

