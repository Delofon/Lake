#include <stdio.h>
#include <stdint.h>

#include <input.h>

#define EVZ 32
event_t evs[EVZ];
uint8_t evi = 0;
uint8_t evn = 0;

void input_register(event_t ev)
{
    evs[(evn + evi) % EVZ] = ev;

    evn++;
    evn %= EVZ;
}

event_t input_pop()
{
    if(evn == 0)
        return (event_t){0,0};

    event_t ev = evs[evi];

    evi++;
    evi %= EVZ;
    evn--;
    evn %= EVZ;

    return ev;
}

