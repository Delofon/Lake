#ifndef VGA_H_
#define VGA_H_

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_SIZE (VGA_WIDTH * VGA_HEIGHT)

typedef enum
{
    VGA_BLACK    = 0,
    VGA_BLUE     = 1,
    VGA_GREEN    = 2,
    VGA_CYAN     = 3,
    VGA_RED      = 4,
    VGA_MAGENTA  = 5,
    VGA_BROWN    = 6,
    VGA_LGRAY    = 7,
    VGA_DGRAY    = 8,
    VGA_LBLUE    = 9,
    VGA_LGREEN   = 10,
    VGA_LCYAN    = 11,
    VGA_LRED     = 12,
    VGA_LMAGENTA = 13,
    VGA_LBROWN   = 14,
    VGA_WHITE    = 15
} vgacol_e;

extern size_t vga_x;
extern size_t vga_y;

extern uint8_t vga_color;
extern uint16_t *vga_buf;

static inline void vga_setcol(vgacol_e fg, vgacol_e bg)
{
    vga_color = bg << 4 | fg;
}

static inline size_t vga_coordtoi()
{
    return vga_y * VGA_WIDTH + vga_x;
}

uint8_t vga_init();
void vga_putchar(char c);
void vga_puts(char *s);

#endif // VGA_H_

