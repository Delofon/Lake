#include <stdio.h>
#include <stdint.h>

#include <panic.h>
#include <input.h>

#include "keyboard.h"

// TODO: Maybe should be moved somewhere input device agnostic?
#define KBEVENTS_SZ 4
event_t kbevents[KBEVENTS_SZ];
uint8_t kbeventsi = 0;
uint8_t kbeventsnum = 0;

void kbevent_append(event_t ev)
{
    kbevents[kbeventsi] = ev;
    kbeventsi++;
    if(kbeventsnum == KBEVENTS_SZ)
        kbeventsi %= KBEVENTS_SZ;
    else
        kbeventsnum++;
}

event_t kbevent_pop()
{
    if(kbeventsnum == 0)
        return (event_t){0};

    kbeventsnum--;
    kbeventsi--;
    kbeventsi %= KBEVENTS_SZ;

    return kbevents[kbeventsi];
}

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
                    kbevent_append((event_t){ .key = KEY_U, .press = PRESS });
                else if(scancode == 0x2a)
                    kbevent_append((event_t){ .key = KEY_LSHIFT, .press = PRESS});
                else if(scancode == 0x96)
                    kbevent_append((event_t){ .key = KEY_U, .press = RELEASE});
                else if(scancode == 0xaa)
                    kbevent_append((event_t){ .key = KEY_LSHIFT, .press = RELEASE});
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

