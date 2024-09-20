#ifndef   __XINT_H__
#define   __XINT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



#if defined(XINT_FAST)
    typedef int_fast64_t i64;
    typedef int_fast32_t i32;
    typedef int_fast16_t i16;
    typedef int_fast8_t i8;

    typedef uint_fast64_t u64;
    typedef uint_fast32_t u32;
    typedef uint_fast16_t u16;
    typedef uint_fast8_t u8;
#elif defined(XINT_LEAST)
    typedef int_least64_t i64;
    typedef int_least32_t i32;
    typedef int_least16_t i16;
    typedef int_least8_t i8;

    typedef uint_least64_t u64;
    typedef uint_least32_t u32;
    typedef uint_least16_t u16;
    typedef uint_least8_t u8;
#else
    typedef int64_t i64;
    typedef int32_t i32;
    typedef int16_t i16;
    typedef int8_t i8;

    typedef uint64_t u64;
    typedef uint32_t u32;
    typedef uint16_t u16;
    typedef uint8_t u8;
#endif



#ifdef __cplusplus
}
#endif

#endif /* __XINT_H__ */