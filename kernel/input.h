#ifndef INPUT_H_
#define INPUT_H_

#include <stdint.h>

typedef enum
{
    KEY_RESERVED = 0,

    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_FOUR,
    KEY_FIVE,
    KEY_SIX,
    KEY_SEVEN,
    KEY_EIGHT,
    KEY_NINE,
    KEY_ZERO,
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
    KEY_BACKTICK,

    NUM_WRKEYS,

    KEY_BACKSP = NUM_WRKEYS,
    KEY_RET,

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

