#include <stdio.h>
#include <stdint.h>

#include <panic.h>
#include <input.h>

#include "keyboard.h"

static kbstate_t kbstate = { .state = 0u };
static uint8_t scanstate = 0;

uint8_t scancode = 0;

void processkbscan()
{
    // in scan2, all key events are at most 8 bytes wide
    // FIXME: currently using scan1 as a temporary PoC
    switch(scanstate)
    {
        case 0:
            {
                if(scancode == 0x16)
                    input_register((event_t){ .key = KEY_U, .press = PRESS });
                else if(scancode == 0x2a)
                    input_register((event_t){ .key = KEY_LSHIFT, .press = PRESS});
                else if(scancode == 0x96)
                    input_register((event_t){ .key = KEY_U, .press = RELEASE});
                else if(scancode == 0xaa)
                    input_register((event_t){ .key = KEY_LSHIFT, .press = RELEASE});
                else if(scancode == 0xf0)
                    scanstate++;
            }
            break;
        case 1:
            {}
            break;
        case 2:
            {}
            break;
        case 3:
            {}
            break;
        case 4:
            {}
            break;
        case 5:
            {}
            break;
        case 6:
            {}
            break;
        case 7:
            {}
            break;

        default:
            printf("processkbscan: invalid state %u\n", scanstate);
            panic("bad scan state");
    }
}

