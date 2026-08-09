// Common enough general purpose redefinitions

#ifndef DEF_H_
#define DEF_H_

// compile-time assertion
#define ct_ass _Static_assert

#define sect(x) __attribute__((section(x)))

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// More pleasant <stdint.h>

typedef uintptr_t up;
typedef intptr_t  ip;

typedef uintmax_t um;
typedef intmax_t  im;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint_fast8_t  u8f;
typedef uint_fast16_t u16f;
typedef uint_fast32_t u32f;
typedef uint_fast64_t u64f;

typedef int_fast8_t  i8f;
typedef int_fast16_t i16f;
typedef int_fast32_t i32f;
typedef int_fast64_t i64f;

typedef uint_least8_t  u8l;
typedef uint_least16_t u16l;
typedef uint_least32_t u32l;
typedef uint_least64_t u64l;

typedef int_least8_t  i8l;
typedef int_least16_t i16l;
typedef int_least32_t i32l;
typedef int_least64_t i64l;

#endif

