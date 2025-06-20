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
        vga_buf[i] = vga_color << 8 | ' ';

    vga_cursor_init(14, 15);

    return 0;
}

static uint8_t isputs = 0;
void vga_putchar(const char c)
{
    if(c == '\n')
    {
        vga_linefeed();
        return;
    }

    if(vga_x >= VGA_WIDTH)
        vga_linefeed();

    vga_buf[vga_coordtoi()] = vga_color << 8 | c;
    vga_x++;

    if(!isputs)
        vga_cursor_move(vga_x, vga_y);
}

void vga_puts(const char *s)
{
    isputs = 1;
    while(*s)
        vga_putchar(*(s++));
    vga_cursor_move(vga_x, vga_y);
    isputs = 0;
}

void vga_linefeed()
{
    vga_x = 0;
    vga_y++;

    if(vga_y >= VGA_HEIGHT)
        vga_scroll();
    vga_cursor_move(vga_x, vga_y);
}

void vga_scroll()
{
    vga_y--;
    memmove(vga_buf, vga_buf+VGA_WIDTH, VGA_WIDTH*(VGA_HEIGHT-1)*sizeof(vga_buf));
    for(size_t i = VGA_WIDTH * (VGA_HEIGHT-1); i < VGA_SIZE; i++)
        vga_buf[i] = vga_color << 8 | ' ';
}

