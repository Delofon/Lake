#include <stdio.h>
#include <stdint.h>

#include <input.h>

#define EVENTS_SZ 4
event_t events[EVENTS_SZ];
uint8_t eventsi = 0;
uint8_t eventsnum = 0;

// I haven't checked if any of this works correctly.
void input_register(event_t ev)
{
    events[eventsi] = ev;
    eventsi++;
    if(eventsnum == EVENTS_SZ)
        eventsi %= EVENTS_SZ;
    else
        eventsnum++;
}
event_t input_pop()
{
    if(eventsnum == 0)
        return (event_t){0};

    eventsnum--;
    eventsi--;
    eventsi %= EVENTS_SZ;

    return events[eventsi];
}

