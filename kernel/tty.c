#include <stdio.h>
#include <stdint.h>

#include <panic.h>
#include <input.h>

#include <arch/i386/vga.h>

typedef union
{
    uint8_t state;
    struct
    {
        uint8_t null : 5;

        uint8_t ctrl  : 1;
        uint8_t shift : 1;
        uint8_t alt   : 1;
    };
} ttystate_t;

ttystate_t ttystate = { .state = 0u };

const char lkeytoascii[NUM_WRKEYS] = "\0001234567890-=qwertyuiop[]asdfghjkl;'\\zxcvbnm,./ \n`";
const char ukeytoascii[NUM_WRKEYS] = "\000!@#$%^&*()_+QWERTYUIOP{}ASDFGHJKL:\"|ZXCVBNM<>? \n~";

void processevent(event_t event)
{
    key_t key = event.key;
    if(key == KEY_RESERVED)
        return;

    // TODO: add an abstraction layer for vga access
    if(key == KEY_LSHIFT || key == KEY_RSHIFT)
    {
        ttystate.shift = event.press;
        return;
    }

    if(event.press == RELEASE)
        return;

    if(key == KEY_BKSP)
    {
        vga_x--;
        vga_putchar(' ');
        vga_x--;
        vga_cursor_move(vga_x, vga_y);
    }

    if(key >= NUM_KEYS)
    {
        printf("tty.c_processevent: %u passed as key num\n", key);
        panic("bad event num");
    }

    // probably should handle numpad keys as well
    if(key >= NUM_WRKEYS)
        return;

    if(ttystate.shift)
        putchar(ukeytoascii[key]);
    else
        putchar(lkeytoascii[key]);
}

void processtty()
{
    event_t ev = {0};
    do
    {
        ev = input_pop();
        processevent(ev);
    } while(ev.key != KEY_RESERVED);
}

