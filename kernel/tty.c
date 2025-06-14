#include <stdio.h>
#include <stdint.h>

#include <panic.h>

#include "input.h"

typedef union
{
    uint8_t state;
    struct
    {
        uint8_t ctrl  : 1;
        uint8_t shift : 1;
        uint8_t alt   : 1;
    };
} ttystate_t;

ttystate_t ttystate = { .state = 0u };

const char lkeytoascii[NUM_KEYS] = "\000123456789qwertyuiopasdfghjklzxcvbnm-=\0 \0\n";
const char ukeytoascii[NUM_KEYS] = "\000!@#$%^&*(QWERTYUIOPASDFGHJKLZXCVBNM_+\0 \0\n";

void processevent(key_t key)
{
    if(key == KEY_LSHIFT)
        ttystate.shift = 1;
    else
    {
        if(key >= NUM_KEYS)
        {
            printf("tty.c_processevent: %u passed as key num\n", key);
            panic("bad event num");
        }

        if(ttystate.shift)
            ukeytoascii[key];
        else
            lkeytoascii[key];

    }
}

