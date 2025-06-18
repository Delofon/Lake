#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdint.h>

#include <input.h>

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

        uint8_t num    : 1;
        uint8_t caps   : 1;
        uint8_t scroll : 1;
    };
} kbstate_t;

typedef struct
{
    uint8_t command;
    uint8_t data;
} command_t;

#endif

