#include <stdio.h>
#include <stdint.h>

#include <panic.h>
#include <input.h>

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

const char lkeytoascii[NUM_KEYS] = "\0001234567890qwertyuiopasdfghjklzxcvbnm-=\0 \0\n";
const char ukeytoascii[NUM_KEYS] = "\000!@#$%^&*()QWERTYUIOPASDFGHJKLZXCVBNM_+\0 \0\n";

void processevent(event_t event)
{
    key_t key = event.key;
    if(key == KEY_RESERVED)
        return;

    if(key == KEY_LSHIFT)
    {
        ttystate.shift = event.press;
    }
    else
    {
        if(event.press == RELEASE)
            return;

        if(key >= NUM_KEYS)
        {
            printf("tty.c_processevent: %u passed as key num\n", key);
            panic("bad event num");
        }

        if(ttystate.shift)
            putchar(ukeytoascii[key]);
        else
            putchar(lkeytoascii[key]);

    }
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

