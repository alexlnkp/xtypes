#ifndef   __XVEC_H__
#define   __XVEC_H__

/*
    This header only gives what you ask for. It will only raise errors if used "on its own" / "out of the box".

    To use vec3, vec4 you need to include "xfloat.h".
    To use ivec3, ivec4 you need to include "xint.h".
    To use uvec3, uvec4 you need to define UVEC_IMPLEMENTATION.

    Otherwise the structs and functions are only declared, but NEVER defined.
    To use ANY of the functions, you need to include <math.h> and link against math library.
*/

/**
 * "Floating" vectors (vec3, vec4):
 * * Define VEC_SCALAR_DOUBLE before including this header to use double (double) precision floating pointers for vec3, vec4 (64bit)
 * * Define VEC_SCALAR_LONG_DOUBLE before including this header to use quadruple (long double) precision floating pointers for vec3, vec4 (128bit*)
 * * Don't define any of the above before including this header to use standard (float) precision floating pointers for vec3, vec4 (32bit)
 * 
 * "Integer" vectors (ivec3, ivec4):
 * * Define VEC_ISCALAR_LONG before including this header to use i64 (int*64_t)
 * * Define VEC_ISCALAR_SHORT before including this header to use i16 (int*16_t)
 * * Don't define any of the above before including this header to use i32 (int*32_t)
 */

#ifdef __cplusplus
extern "C" {
#endif



#ifdef    __XFLOAT_H__
    #ifdef VEC_SCALAR_DOUBLE
        typedef f64 __scalar;
    #elif defined(VEC_SCALAR_LONG_DOUBLE)
        typedef f128 __scalar;
    #else
        typedef f32 __scalar;
    #endif
#else
    typedef float __scalar;
#endif /* __XFLOAT_H__ */

#ifdef    __XINT_H__
    #ifdef VEC_ISCALAR_LONG
        typedef i64 __iscalar;
    #elif defined(VEC_ISCALAR_SHORT)
        typedef i16 __iscalar;
    #else
        typedef i32 __iscalar;
    #endif
#else
    typedef int __iscalar;
#endif /* __XINT_H__ */

#ifdef    UVEC_IMPLEMENTATION
    #ifdef VEC_ISCALAR_LONG
        typedef u64 __uscalar;
    #elif defined(VEC_ISCALAR_SHORT)
        typedef u16 __uscalar;
    #else
        typedef u32 __uscalar;
    #endif
#else
    typedef unsigned __uscalar;
#endif /* UVEC_IMPLEMENTATION */

#define X_DECLARE_VEC_FUNC(t, n) \
    t##vec##n t##vec##n##_zero(void); \
    t##vec##n t##vec##n##_one(void); \
    t##vec##n t##vec##n##_add(t##vec##n v1, t##vec##n v2); \
    t##vec##n t##vec##n##_sub(t##vec##n v1, t##vec##n v2); \
    t##vec##n t##vec##n##_add_val(t##vec##n v1, __##t##scalar f); \
    t##vec##n t##vec##n##_sub_val(t##vec##n v1, __##t##scalar f); \
    t##vec##n t##vec##n##_scale(t##vec##n v1, __##t##scalar f); \
    t##vec##n t##vec##n##_multiply(t##vec##n v1, t##vec##n v2); \
    __##t##scalar t##vec##n##_dot(t##vec##n v1, t##vec##n v2); \
    t##vec##n t##vec##n##_cross(t##vec##n v1, t##vec##n v2); \
    __##t##scalar t##vec##n##_magnitude(t##vec##n v); \
    t##vec##n t##vec##n##_normalize(t##vec##n v);

typedef struct vec3 vec3;
typedef struct vec4 vec4;

typedef struct ivec3 ivec3;
typedef struct ivec4 ivec4;

typedef struct uvec3 uvec3;
typedef struct uvec4 uvec4;

X_DECLARE_VEC_FUNC(, 3);
X_DECLARE_VEC_FUNC(, 4);

X_DECLARE_VEC_FUNC(i, 3);
X_DECLARE_VEC_FUNC(i, 4);

X_DECLARE_VEC_FUNC(u, 3);
X_DECLARE_VEC_FUNC(u, 4);

#define X_DEFINE_VEC3_FUNC(t)    \
    t##vec3 t##vec3_zero(void) { \
        t##vec3 result = { 0.0f, 0.0f, 0.0f }; \
        return result; \
    } \
    t##vec3 t##vec3_one(void) { \
        t##vec3 result = { 1.0f, 1.0f, 1.0f }; \
        return result; \
    } \
    t##vec3 t##vec3_add(t##vec3 v1, t##vec3 v2) { \
        t##vec3 result = {  \
            v1.x + v2.x,    \
            v1.y + v2.y,    \
            v1.z + v2.z     \
        };                  \
                            \
        return result;      \
    } \
    t##vec3 t##vec3_sub(t##vec3 v1, t##vec3 v2) { \
        t##vec3 result = {  \
            v1.x - v2.x,    \
            v1.y - v2.y,    \
            v1.z - v2.z     \
        };                  \
                            \
        return result;      \
    } \
    t##vec3 t##vec3_add_val(t##vec3 v1, __##t##scalar f) { \
        t##vec3 result = {  \
            v1.x + f,       \
            v1.y + f,       \
            v1.z + f        \
        };                  \
                            \
        return result;      \
    } \
    t##vec3 t##vec3_sub_val(t##vec3 v1, __##t##scalar f) { \
        t##vec3 result = {  \
            v1.x - f,       \
            v1.y - f,       \
            v1.z - f        \
        };                  \
                            \
        return result;      \
    } \
    t##vec3 t##vec3_scale(t##vec3 v1, __##t##scalar f) { \
        t##vec3 result = {  \
            v1.x * f,       \
            v1.y * f,       \
            v1.z * f        \
        };                  \
                            \
        return result;      \
    } \
    t##vec3 t##vec3_multiply(t##vec3 v1, t##vec3 v2) { \
        t##vec3 result = {  \
            v1.x * v2.x,    \
            v1.y * v2.y,    \
            v1.z * v2.z     \
        };                  \
                            \
        return result;      \
    } \
    __##t##scalar t##vec3_dot(t##vec3 v1, t##vec3 v2) {   \
        __##t##scalar result = (                          \
            (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) \
        );                                                \
        return result;                                    \
    } \
    t##vec3 t##vec3_cross(t##vec3 v1, t##vec3 v2) { \
        t##vec3 result = {             \
            v1.y * v2.z - v1.z * v2.y, \
            v1.z * v2.x - v1.x * v2.z, \
            v1.x * v2.y - v1.y * v2.x  \
        };                             \
        return result;                 \
    } \
    __##t##scalar t##vec3_magnitude(t##vec3 v) {    \
        return sqrt(                                \
            (v.x * v.x) + (v.y * v.y) + (v.z * v.z) \
        );                                          \
    } \
    t##vec3 t##vec3_normalize(t##vec3 v) { \
        __##t##scalar mag = t##vec3_magnitude(v); \
        return t##vec3_scale(v, 1.0f / mag); \
    }


#define X_DEFINE_VEC4_FUNC(t) \
    t##vec4 t##vec4_zero(void) { \
        t##vec4 result = { 0.0f, 0.0f, 0.0f, 0.0f }; \
        return result; \
    } \
    t##vec4 t##vec4_one(void) { \
        t##vec4 result = { 1.0f, 1.0f, 1.0f, 1.0f }; \
        return result; \
    } \
    t##vec4 t##vec4_add(t##vec4 v1, t##vec4 v2) { \
        t##vec4 result = {  \
            v1.x + v2.x,    \
            v1.y + v2.y,    \
            v1.z + v2.z,    \
            v1.w + v2.w     \
        };                  \
                            \
        return result;      \
    } \
    t##vec4 t##vec4_sub(t##vec4 v1, t##vec4 v2) { \
        t##vec4 result = {  \
            v1.x - v2.x,    \
            v1.y - v2.y,    \
            v1.z - v2.z,    \
            v1.w - v2.w     \
        };                  \
                            \
        return result;      \
    } \
    t##vec4 t##vec4_add_val(t##vec4 v1, __##t##scalar f) { \
        t##vec4 result = {  \
            v1.x + f,       \
            v1.y + f,       \
            v1.z + f,       \
            v1.w + f        \
        };                  \
                            \
        return result;      \
    } \
    t##vec4 t##vec4_sub_val(t##vec4 v1, __##t##scalar f) { \
        t##vec4 result = {  \
            v1.x - f,       \
            v1.y - f,       \
            v1.z - f,       \
            v1.w - f        \
        };                  \
                            \
        return result;      \
    } \
    t##vec4 t##vec4_scale(t##vec4 v1, __##t##scalar f) { \
        t##vec4 result = {  \
            v1.x * f,       \
            v1.y * f,       \
            v1.z * f,       \
            v1.w * f        \
        };                  \
                            \
        return result;      \
    } \
    t##vec4 t##vec4_multiply(t##vec4 v1, t##vec4 v2) { \
        t##vec4 result = {  \
            v1.x * v2.x,    \
            v1.y * v2.y,    \
            v1.z * v2.z,    \
            v1.w * v2.w     \
        };                  \
        return result;      \
    } \
    __##t##scalar t##vec4_dot(t##vec4 v1, t##vec4 v2) { \
        __##t##scalar result = (            \
            (v1.x * v2.x) + (v1.y * v2.y) + \
            (v1.z * v2.z) + (v1.w * v2.w)   \
        );                                  \
        return result;                      \
    } \
    /* The cross product of two 4d vectors is not defined. just return t##vec4_zero() */ \
    t##vec4 t##vec4_cross(t##vec4 v1, t##vec4 v2) {  \
        t##vec4 result = t##vec4_zero(); \
        return result;                   \
    } \
    __##t##scalar t##vec4_magnitude(t##vec4 v) { \
        return sqrt(                    \
            (v.x * v.x) + (v.y * v.y) + \
            (v.z * v.z) + (v.w * v.w)   \
        );                              \
    } \
    t##vec4 t##vec4_normalize(t##vec4 v) { \
        __##t##scalar mag = t##vec4_magnitude(v); \
        return t##vec4_scale(v, 1.0f / mag); \
    }

#ifdef    __XFLOAT_H__
    typedef struct vec3 {
        __scalar x, y, z;
    } vec3;

    typedef struct vec4 {
        __scalar x, y, z, w;
    } vec4;

    X_DEFINE_VEC3_FUNC();
    X_DEFINE_VEC4_FUNC();

#endif /* __XFLOAT_H__ */

#ifdef    __XINT_H__
    typedef struct ivec3 {
        __iscalar x, y, z;
    } ivec3;

    typedef struct ivec4 {
        __iscalar x, y, z, w;
    } ivec4;

    X_DEFINE_VEC3_FUNC(i);
    X_DEFINE_VEC4_FUNC(i);

    #ifdef    UVEC_IMPLEMENTATION
        typedef struct uvec3 {
            __uscalar x, y, z;
        } uvec3;

        typedef struct uvec4 {
            __uscalar x, y, z, w;
        } uvec4;

        X_DEFINE_VEC3_FUNC(u);
        X_DEFINE_VEC4_FUNC(u);

    #endif /* UVEC_IMPLEMENTATION */
#endif /* __XINT_H__ */


#ifdef __cplusplus
}
#endif

#endif /* __XVEC_H__*/