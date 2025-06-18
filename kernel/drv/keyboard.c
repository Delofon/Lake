#include <stdio.h>
#include <stdint.h>

#include <io.h>

#include <panic.h>
#include <input.h>

#include "keyboard.h"

static kbstate_t kbstate = { .state = 0u };
static uint8_t scanstate = 0;

void kb_init()
{
    // TODO: switch to scan code set 2, somehow work with i8042.c
}

uint8_t scancode = 0;
void keyboard_irq()
{
    uint8_t status = inb(0x64);

    if(status & 0x1)
    {
        io_wait();
        scancode = inb(0x60);
    }
}

uint8_t release = 0;

void processkbscan()
{
    if(scancode == 0)
        return;

    // handle response codes
    switch(scancode)
    {
        case KB_ERR1:
        case KB_ERR2:
            // do something?
            scancode = 0;
            return;
        // KB_TEST_GOOD response code 0xaa conflicts with
        // lshift scan1 release code 0xaa
        //case KB_TEST_GOOD:
        //    // TODO: confirm kb self test
        //    scancode = 0;
        //    return;
        case KB_ECHO:
            // echo successful
            scancode = 0;
            return;
        case KB_ACK:
            // TODO: pop command
            scancode = 0;
            return;
        case KB_TEST_BAD1:
        case KB_TEST_BAD2:
            // do something?
            scancode = 0;
            return;
        case KB_RESEND:
            // TODO: resend command
            scancode = 0;
            return;
    }

    // in scan2, all key events are at most 8 bytes wide
    // FIXME: currently using scan1 as a temporary PoC
    switch(scanstate)
    {
        case 0:
            {
                //if(scancode == KB_REL)
                //    release = 1;

                if(scancode == 0x16)
                    input_register((event_t){ .key = KEY_U, .press = PRESS });
                else if(scancode == 0x2a)
                    input_register((event_t){ .key = KEY_LSHIFT, .press = PRESS});
                else if(scancode == 0x96)
                    input_register((event_t){ .key = KEY_U, .press = RELEASE});
                else if(scancode == 0xaa)
                    input_register((event_t){ .key = KEY_LSHIFT, .press = RELEASE});

                scancode = 0;
            }
            break;
        default:
            printf("processkbscan: invalid state %u\n", scanstate);
            panic("bad scan state");
    }
}

