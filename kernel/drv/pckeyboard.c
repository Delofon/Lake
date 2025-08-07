#include <stdio.h>
#include <stdint.h>

#include <io.h>

#include <panic.h>
#include <input.h>

#include "pckeyboard.h"
#include "ps2_scan.h"

static kbstate_t kbstate = { .state = 0u };

#define SCZ 16
uint8_t scs[SCZ] = {0};
uint8_t sci = 0;
uint8_t scn = 0;
uint8_t *scp = scs;

void sc_push(uint8_t sc)
{
    *scp = sc;
    scn++;
    scn %= SCZ;

    scp = scs + (scn+sci)%SCZ;
}
uint8_t sc_pop()
{
    if(scn == 0)
        return 0;

    uint8_t sc = scs[sci];

    scn--;
    sci++;
    sci %= SCZ;

    scp = scs + (scn+sci)%SCZ;

    return sc;
}

void keyboard_irq()
{
    uint8_t status = inb(0x64);

    if(status & 0x1)
    {
        io_wait();
        uint8_t sc = inb(0x60);
        sc_push(sc);
    }
}

void hang();

// TODO: properly test PS/2
void ps2_init()
{
    outb(0x64, 0x20);
    io_wait();
    uint8_t config = sc_pop();
    config &= 0b00111111;
    outb(0x64, 0x60);
    io_wait();
    uint8_t status = inb(0x64);

    // do something better? assuming PIT works as expected here
    while(status & 0x2) hang();
    io_wait();
    outb(0x60, config);
}

void kb_init()
{
    // TODO: ensure scan2 is actually set
    kbstate.scan = SCAN2;
    outb(0x60, 2);

    uint8_t sc;
    if((sc = sc_pop()) != 0)
    {
        //printf("unhandled 0x%02x 0x%02x\n", sc, *(scp));
    }
}

void processkbscan()
{
    static uint8_t scanstate = 0;
    static uint8_t ofs = 0;

    uint8_t sc;
    while((sc = sc_pop()) != 0)
    {
        //printf("parsing 0x%02x\n", sc);

        if(sc == 0xf0)
        {
            kbstate.release = 1;
            continue;
        }

        switch(scanstate)
        {
            case 0:
                if(sc == 0xe1)
                {
                    // this is pause pressed
                    scanstate = 1;
                    break;
                }
                if(sc == 0xe0)
                {
                    ofs = 0x80;
                    break;
                }
                input_register((event_t){scan2[sc+ofs], !kbstate.release});
                ofs = 0;
                kbstate.release = 0;
                break;
            case 1:
                if(sc == 0x77)
                    scanstate++;
                break;
            case 2:
                if(sc == 0x77)
                {
                    input_register((event_t){KEY_PAUSE, PRESS});
                    input_register((event_t){KEY_PAUSE, RELEASE});
                    kbstate.release = 0;
                    scanstate = 0;
                }
                break;
            default:
                printf("processkbscan: invalid state %u\n", scanstate);
                panic("bad scan state");
        }
    }
}

