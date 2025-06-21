#ifndef INPUT_H_
#define INPUT_H_

#include <stdint.h>

typedef enum
{
    KEY_RESERVED = 0,

    // ASCII
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_MINUS,
    KEY_EQUALS,

    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_LBRACE,
    KEY_RBRACE,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_COLON,
    KEY_APOS,
    KEY_BSLASH,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    KEY_COMMA,
    KEY_DOT,
    KEY_SLASH,

    KEY_SPACE,
    KEY_RET,
    KEY_BKT,

    NUM_WRKEYS,

    KEY_BACKSP = NUM_WRKEYS,

    KEY_ESC,
    KEY_TAB,
    KEY_CAPS,

    KEY_LSHIFT,
    KEY_RSHIFT,
    KEY_LCTRL,
    KEY_RCTRL,
    KEY_LALT,
    KEY_RALT,
    KEY_LMETA,
    KEY_RMETA,
    KEY_LIST,

    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    KEY_PRTSCR,
    KEY_SCROLL,
    KEY_PAUSE,
    KEY_INS,
    KEY_HOME,
    KEY_PGUP,
    KEY_DEL,
    KEY_END,
    KEY_PGDN,

    KEY_LEFT,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,

    // numpad
    KEY_NUM,
    KEY_NSLASH,
    KEY_NMUL,
    KEY_NSUB,
    KEY_NSEVEN,
    KEY_NEIGHT,
    KEY_NNINE,
    KEY_NADD,
    KEY_NFOUR,
    KEY_NFIVE,
    KEY_NSIX,
    KEY_NONE,
    KEY_NTWO,
    KEY_NTHREE,
    KEY_NRET,
    KEY_NZERO,
    KEY_NDOT,

    // multimedia
    KEY_WWW,
    KEY_PTRACK,
    KEY_WWWFAV,
    KEY_WWWREF,
    KEY_DVOL,
    KEY_MUTE,
    KEY_WWWSTOP,
    KEY_CALC,
    KEY_WWWFOR,
    KEY_IVOL,
    KEY_PLAY,
    KEY_WWWBACK,
    KEY_WWWHOME,
    KEY_STOP,
    KEY_PC,
    KEY_MAIL,
    KEY_NTRACK,
    KEY_SEL,

    // acpi
    KEY_POWER,
    KEY_SLEEP,
    KEY_WAKE,

    NUM_KEYS
} key_t;

typedef enum
{
    RELEASE,
    PRESS
} press_t;

typedef struct
{
    key_t key;
    press_t press;
} event_t;

void input_register(event_t ev);
event_t input_pop();

#endif

