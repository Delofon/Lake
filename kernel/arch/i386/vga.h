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
} vgacol_t;

extern size_t vga_x;
extern size_t vga_y;

extern uint8_t vga_color;
extern uint16_t *vga_buf;

uint8_t vga_init();
void vga_putchar(const char c);
void vga_puts(const char *s);
void vga_linefeed();
void vga_scroll();

void vga_cursor_init(size_t start_scanline, size_t end_scanline);
void vga_cursor_move(size_t vga_x, size_t vga_y);

static inline void vga_setcol(vgacol_t fg, vgacol_t bg)
{
    vga_color = bg << 4 | fg;
}

static inline size_t vga_coordtoi()
{
    return vga_y * VGA_WIDTH + vga_x;
}

#endif // VGA_H_

