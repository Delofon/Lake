#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdint.h>

typedef enum
{
    SCAN1 = 0,
    SCAN2,
    SCAN3
} scanset_t;

typedef union
{
    uint8_t state;
    struct
    {
        uint8_t null : 3;

        scanset_t scan : 2;

        uint8_t numlock   : 1;
        uint8_t capslock  : 1;
        uint8_t scrollock : 1;
    };
} kbstate_t;

#endif

