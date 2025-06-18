#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdint.h>

#include <input.h>

// response codes
#define KB_ERR1 0x00
#define KB_ERR2 0xff
#define KB_TEST_GOOD 0xaa
#define KB_ECHO 0xee
#define KB_ACK 0xfa
#define KB_TEST_BAD1 0xfc
#define KB_TEST_BAD2 0xfd
#define KB_RESEND 0xfe

// scan codes
#define KB_REL 0xf0

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
} kbcommand_t;

void processkbscan();

#endif

