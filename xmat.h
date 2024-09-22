/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose unless specified otherwise, commercial or
non-commercial, and by any means, with the exception of use for
training AI systems, as explained below.

NOTICE: The usage of this software or its source code by artificial
intelligence systems, including but not limited to datasets, training,
or any other AI-related activities, is strictly prohibited.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * DISCLAIMER: Major portions of this header were based off of <raymath.h> , which
 * was originally made by Ramon Santamaria (@raysan5)
 * * SOURCE: https://github.com/raysan5/raylib/blob/master/src/raymath.h
 */

/** 
 * WARNING: This header only gives what you ask for. It will only raise errors if used "on its own" / "out of the box".
 * You need to include <math.h> and link against standard math library (-lm).
 * To use mat4x4 and its functions, define XMAT4X4_DEFINITION before including this header.
 * To use mat3x3 and its functions, define XMAT3X3_DEFINITION before including this header.
 * If you want to use special scalar types listed below, you need to include <xfloat.h> before including this header
 * 
 * Scalar types for mat3x3 and mat4x4:
 * * Define MAT_SCALAR_DOUBLE before including this header to use double (double) precision floating pointers (64bit)
 * * Define MAT_SCALAR_LONG_DOUBLE before including this header to use quadruple (long double) precision floating pointers (128bit*)
 * * Don't define any of the above before including this header to use standard (float) precision floating pointers (32bit)
 * 
*/


#ifndef   __XMAT_H__
#define   __XMAT_H__

#ifdef    __XFLOAT_H__
    #ifdef MAT_SCALAR_DOUBLE
        typedef f64 __mat_scalar;
    #elif defined(MAT_SCALAR_LONG_DOUBLE)
        typedef f128 __mat_scalar;
    #else
        typedef f32 __mat_scalar;
    #endif
#else
    typedef float __mat_scalar;
#endif /* __XFLOAT_H__ */



typedef struct mat3x3 mat3x3;
typedef struct mat4x4 mat4x4;

mat3x3 mat3x3_zero(void);
mat3x3 mat3x3_identity(void);
mat3x3 mat3x3_add(mat3x3 mat1, mat3x3 mat2);
mat3x3 mat3x3_sub(mat3x3 mat1, mat3x3 mat2);
mat3x3 mat3x3_multiply(mat3x3 left, mat3x3 right);
mat3x3 mat3x3_transpose(mat3x3 mat);
__mat_scalar mat3x3_det(mat3x3 mat);
mat3x3 mat3x3_invert(mat3x3 mat);

mat4x4 mat4x4_zero(void);
mat4x4 mat4x4_identity(void);
mat4x4 mat4x4_add(mat4x4 mat1, mat4x4 mat2);
mat4x4 mat4x4_sub(mat4x4 mat1, mat4x4 mat2);
mat4x4 mat4x4_multiply(mat4x4 left, mat4x4 right);
mat4x4 mat4x4_transpose(mat4x4 mat);
__mat_scalar mat4x4_det(mat4x4 mat);
mat4x4 mat4x4_invert(mat4x4 mat);



#ifdef    XMAT3X3_DEFINITION
    typedef struct mat3x3 {
        __mat_scalar m0, m3, m6; // Matrix first  row (3 components)
        __mat_scalar m1, m4, m7; // Matrix second row (3 components)
        __mat_scalar m2, m5, m8; // Matrix third  row (3 components)
    } mat3x3;

    mat3x3 mat3x3_zero(void) {
        mat3x3 result = {
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        };

        return result;
    }

    mat3x3 mat3x3_identity(void) {
        mat3x3 result = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        return result;
    }

    mat3x3 mat3x3_add(mat3x3 mat1, mat3x3 mat2) {
        mat3x3 result = {
            (mat1.m0 + mat2.m0), (mat1.m3 + mat2.m3), (mat1.m6 + mat2.m6),
            (mat1.m1 + mat2.m1), (mat1.m4 + mat2.m4), (mat1.m7 + mat2.m7),
            (mat1.m2 + mat2.m2), (mat1.m5 + mat2.m5), (mat1.m8 + mat2.m8)
        };

        return result;
    }

    mat3x3 mat3x3_sub(mat3x3 mat1, mat3x3 mat2) {
        mat3x3 result = {
            (mat1.m0 - mat2.m0), (mat1.m3 - mat2.m3), (mat1.m6 - mat2.m6),
            (mat1.m1 - mat2.m1), (mat1.m4 - mat2.m4), (mat1.m7 - mat2.m7),
            (mat1.m2 - mat2.m2), (mat1.m5 - mat2.m5), (mat1.m8 - mat2.m8)
        };

        return result;
    }

    mat3x3 mat3x3_multiply(mat3x3 left, mat3x3 right) {
        mat3x3 result = mat3x3_zero();

        result.m0 = ((left.m0 * right.m0) + (left.m3 * right.m1) + (left.m6 * right.m2));
        result.m3 = ((left.m0 * right.m3) + (left.m3 * right.m4) + (left.m6 * right.m5));
        result.m6 = ((left.m0 * right.m6) + (left.m3 * right.m7) + (left.m6 * right.m8));

        result.m1 = ((left.m1 * right.m0) + (left.m4 * right.m1) + (left.m7 * right.m2));
        result.m4 = ((left.m1 * right.m3) + (left.m4 * right.m4) + (left.m7 * right.m5));
        result.m7 = ((left.m1 * right.m6) + (left.m4 * right.m7) + (left.m7 * right.m8));

        result.m2 = ((left.m2 * right.m0) + (left.m5 * right.m1) + (left.m8 * right.m2));
        result.m5 = ((left.m2 * right.m3) + (left.m5 * right.m4) + (left.m8 * right.m5));
        result.m8 = ((left.m2 * right.m6) + (left.m5 * right.m7) + (left.m8 * right.m8));

        return result;
    }

    mat3x3 mat3x3_transpose(mat3x3 mat) {
        mat3x3 result = mat3x3_zero();

        result = (mat3x3) {
            mat.m0, mat.m1, mat.m2,
            mat.m3, mat.m4, mat.m5,
            mat.m6, mat.m7, mat.m8
        };

        return result;
    }

    __mat_scalar mat3x3_det(mat3x3 mat) {
        __mat_scalar result = 0;

        result = (
            ((mat.m0 * mat.m4 * mat.m8) + (mat.m3 * mat.m7 * mat.m2) + (mat.m6 * mat.m1 * mat.m5)) -
            ((mat.m2 * mat.m4 * mat.m6) + (mat.m5 * mat.m7 * mat.m0) + (mat.m8 * mat.m1 * mat.m3))
        );

        return result;
    }

    mat3x3 mat3x3_invert(mat3x3 mat) {
        mat3x3 result = mat3x3_zero();

        __mat_scalar a00 = mat.m0, a01 = mat.m1, a02 = mat.m2;
        __mat_scalar a10 = mat.m3, a11 = mat.m4, a12 = mat.m5;
        __mat_scalar a20 = mat.m6, a21 = mat.m7, a22 = mat.m8;

        __mat_scalar b00 = ((a11 * a22) - (a12 * a21));
        __mat_scalar b01 = ((a02 * a21) - (a01 * a22));
        __mat_scalar b02 = ((a01 * a12) - (a02 * a11));
        __mat_scalar b10 = ((a12 * a20) - (a10 * a22));
        __mat_scalar b11 = ((a00 * a22) - (a02 * a20));
        __mat_scalar b12 = ((a02 * a10) - (a00 * a12));
        __mat_scalar b20 = ((a10 * a21) - (a11 * a20));
        __mat_scalar b21 = ((a01 * a20) - (a00 * a21));
        __mat_scalar b22 = ((a00 * a11) - (a01 * a10));

        __mat_scalar det = ((a00 * b00) + (a01 * b10) + (a02 * b20));
        __mat_scalar invDet = powf(det, -1.0f * (det != 0)) * (det != 0);

        result.m0 = b00 * invDet;
        result.m1 = b01 * invDet;
        result.m2 = b02 * invDet;
        result.m3 = b10 * invDet;
        result.m4 = b11 * invDet;
        result.m5 = b12 * invDet;
        result.m6 = b20 * invDet;
        result.m7 = b21 * invDet;
        result.m8 = b22 * invDet;

        return result;
    }

#endif /* XMAT3X3_DEFINITION */

#ifdef    XMAT4X4_DEFINITION
    typedef struct mat4x4 {
        __mat_scalar m0, m4, m8, m12;  // Matrix first  row (4 components)
        __mat_scalar m1, m5, m9, m13;  // Matrix second row (4 components)
        __mat_scalar m2, m6, m10, m14; // Matrix third  row (4 components)
        __mat_scalar m3, m7, m11, m15; // Matrix fourth row (4 components)
    } mat4x4;

    mat4x4 mat4x4_zero(void) {
        mat4x4 result = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };

        return result;
    }

    mat4x4 mat4x4_identity(void) {
        mat4x4 result = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return result;
    }

    mat4x4 mat4x4_add(mat4x4 mat1, mat4x4 mat2) {
        mat4x4 result = {
            (mat1.m0 + mat2.m0), (mat1.m4 + mat2.m4), ( mat1.m8 + mat2.m8 ), (mat1.m12 + mat2.m12),
            (mat1.m1 + mat2.m1), (mat1.m5 + mat2.m5), ( mat1.m9 + mat2.m9 ), (mat1.m13 + mat2.m13),
            (mat1.m2 + mat2.m2), (mat1.m6 + mat2.m6), (mat1.m10 + mat2.m10), (mat1.m14 + mat2.m14),
            (mat1.m3 + mat2.m3), (mat1.m7 + mat2.m7), (mat1.m11 + mat2.m11), (mat1.m15 + mat2.m15)
        };

        return result;
    }

    mat4x4 mat4x4_sub(mat4x4 mat1, mat4x4 mat2) {
        mat4x4 result = {
            (mat1.m0 - mat2.m0), (mat1.m4 - mat2.m4), ( mat1.m8 - mat2.m8 ), (mat1.m12 - mat2.m12),
            (mat1.m1 - mat2.m1), (mat1.m5 - mat2.m5), ( mat1.m9 - mat2.m9 ), (mat1.m13 - mat2.m13),
            (mat1.m2 - mat2.m2), (mat1.m6 - mat2.m6), (mat1.m10 - mat2.m10), (mat1.m14 - mat2.m14),
            (mat1.m3 - mat2.m3), (mat1.m7 - mat2.m7), (mat1.m11 - mat2.m11), (mat1.m15 - mat2.m15)
        };

        return result;
    }

    mat4x4 mat4x4_multiply(mat4x4 left, mat4x4 right) {
        mat4x4 result = mat4x4_zero();

        result.m0  = (left.m0  * right.m0) + (left.m1  * right.m4) + (left.m2  * right.m8 ) + (left.m3  * right.m12);
        result.m1  = (left.m0  * right.m1) + (left.m1  * right.m5) + (left.m2  * right.m9 ) + (left.m3  * right.m13);
        result.m2  = (left.m0  * right.m2) + (left.m1  * right.m6) + (left.m2  * right.m10) + (left.m3  * right.m14);
        result.m3  = (left.m0  * right.m3) + (left.m1  * right.m7) + (left.m2  * right.m11) + (left.m3  * right.m15);
        result.m4  = (left.m4  * right.m0) + (left.m5  * right.m4) + (left.m6  * right.m8 ) + (left.m7  * right.m12);
        result.m5  = (left.m4  * right.m1) + (left.m5  * right.m5) + (left.m6  * right.m9 ) + (left.m7  * right.m13);
        result.m6  = (left.m4  * right.m2) + (left.m5  * right.m6) + (left.m6  * right.m10) + (left.m7  * right.m14);
        result.m7  = (left.m4  * right.m3) + (left.m5  * right.m7) + (left.m6  * right.m11) + (left.m7  * right.m15);
        result.m8  = (left.m8  * right.m0) + (left.m9  * right.m4) + (left.m10 * right.m8 ) + (left.m11 * right.m12);
        result.m9  = (left.m8  * right.m1) + (left.m9  * right.m5) + (left.m10 * right.m9 ) + (left.m11 * right.m13);
        result.m10 = (left.m8  * right.m2) + (left.m9  * right.m6) + (left.m10 * right.m10) + (left.m11 * right.m14);
        result.m11 = (left.m8  * right.m3) + (left.m9  * right.m7) + (left.m10 * right.m11) + (left.m11 * right.m15);
        result.m12 = (left.m12 * right.m0) + (left.m13 * right.m4) + (left.m14 * right.m8 ) + (left.m15 * right.m12);
        result.m13 = (left.m12 * right.m1) + (left.m13 * right.m5) + (left.m14 * right.m9 ) + (left.m15 * right.m13);
        result.m14 = (left.m12 * right.m2) + (left.m13 * right.m6) + (left.m14 * right.m10) + (left.m15 * right.m14);
        result.m15 = (left.m12 * right.m3) + (left.m13 * right.m7) + (left.m14 * right.m11) + (left.m15 * right.m15);

        return result;
    }

    mat4x4 mat4x4_transpose(mat4x4 mat) {
        mat4x4 result = mat4x4_zero();

        result = (mat4x4) {
            mat.m0,  mat.m1,  mat.m2,  mat.m3,
            mat.m4,  mat.m5,  mat.m6,  mat.m7,
            mat.m8,  mat.m9,  mat.m10, mat.m11,
            mat.m12, mat.m13, mat.m14, mat.m15
        };

        return result;
    }

    __mat_scalar mat4x4_det(mat4x4 mat) {
        __mat_scalar result = 0.0f;

        __mat_scalar a00 = mat.m0,  a01 = mat.m1,  a02 = mat.m2,  a03 = mat.m3;
        __mat_scalar a10 = mat.m4,  a11 = mat.m5,  a12 = mat.m6,  a13 = mat.m7;
        __mat_scalar a20 = mat.m8,  a21 = mat.m9,  a22 = mat.m10, a23 = mat.m11;
        __mat_scalar a30 = mat.m12, a31 = mat.m13, a32 = mat.m14, a33 = mat.m15;

        result = (a30 * a21 * a12 * a03) - (a20 * a31 * a12 * a03) - (a30 * a11 * a22 * a03) + (a10 * a31 * a22 * a03) +
                 (a20 * a11 * a32 * a03) - (a10 * a21 * a32 * a03) - (a30 * a21 * a02 * a13) + (a20 * a31 * a02 * a13) +
                 (a30 * a01 * a22 * a13) - (a00 * a31 * a22 * a13) - (a20 * a01 * a32 * a13) + (a00 * a21 * a32 * a13) +
                 (a30 * a11 * a02 * a23) - (a10 * a31 * a02 * a23) - (a30 * a01 * a12 * a23) + (a00 * a31 * a12 * a23) +
                 (a10 * a01 * a32 * a23) - (a00 * a11 * a32 * a23) - (a20 * a11 * a02 * a33) + (a10 * a21 * a02 * a33) +
                 (a20 * a01 * a12 * a33) - (a00 * a21 * a12 * a33) - (a10 * a01 * a22 * a33) + (a00 * a11 * a22 * a33);

        return result;
    }

    mat4x4 mat4x4_invert(mat4x4 mat) {
        mat4x4 result = mat4x4_zero();

        __mat_scalar a00 = mat.m0,  a01 = mat.m1,  a02 = mat.m2,  a03 = mat.m3;
        __mat_scalar a10 = mat.m4,  a11 = mat.m5,  a12 = mat.m6,  a13 = mat.m7;
        __mat_scalar a20 = mat.m8,  a21 = mat.m9,  a22 = mat.m10, a23 = mat.m11;
        __mat_scalar a30 = mat.m12, a31 = mat.m13, a32 = mat.m14, a33 = mat.m15;

        __mat_scalar b00 = (a00 * a11) - (a01 * a10);
        __mat_scalar b01 = (a00 * a12) - (a02 * a10);
        __mat_scalar b02 = (a00 * a13) - (a03 * a10);
        __mat_scalar b03 = (a01 * a12) - (a02 * a11);
        __mat_scalar b04 = (a01 * a13) - (a03 * a11);
        __mat_scalar b05 = (a02 * a13) - (a03 * a12);
        __mat_scalar b06 = (a20 * a31) - (a21 * a30);
        __mat_scalar b07 = (a20 * a32) - (a22 * a30);
        __mat_scalar b08 = (a20 * a33) - (a23 * a30);
        __mat_scalar b09 = (a21 * a32) - (a22 * a31);
        __mat_scalar b10 = (a21 * a33) - (a23 * a31);
        __mat_scalar b11 = (a22 * a33) - (a23 * a32);

        __mat_scalar invDet = 1.0f / ((b00 * b11) - (b01 * b10) + (b02 * b09) + (b03 * b08) - (b04 * b07) + (b05 * b06));

        result.m0  = (( a11 * b11) - (a12 * b10) + (a13 * b09)) * invDet;
        result.m1  = ((-a01 * b11) + (a02 * b10) - (a03 * b09)) * invDet;
        result.m2  = (( a31 * b05) - (a32 * b04) + (a33 * b03)) * invDet;
        result.m3  = ((-a21 * b05) + (a22 * b04) - (a23 * b03)) * invDet;
        result.m4  = ((-a10 * b11) + (a12 * b08) - (a13 * b07)) * invDet;
        result.m5  = (( a00 * b11) - (a02 * b08) + (a03 * b07)) * invDet;
        result.m6  = ((-a30 * b05) + (a32 * b02) - (a33 * b01)) * invDet;
        result.m7  = (( a20 * b05) - (a22 * b02) + (a23 * b01)) * invDet;
        result.m8  = (( a10 * b10) - (a11 * b08) + (a13 * b06)) * invDet;
        result.m9  = ((-a00 * b10) + (a01 * b08) - (a03 * b06)) * invDet;
        result.m10 = (( a30 * b04) - (a31 * b02) + (a33 * b00)) * invDet;
        result.m11 = ((-a20 * b04) + (a21 * b02) - (a23 * b00)) * invDet;
        result.m12 = ((-a10 * b09) + (a11 * b07) - (a12 * b06)) * invDet;
        result.m13 = (( a00 * b09) - (a01 * b07) + (a02 * b06)) * invDet;
        result.m14 = ((-a30 * b03) + (a31 * b01) - (a32 * b00)) * invDet;
        result.m15 = (( a20 * b03) - (a21 * b01) + (a22 * b00)) * invDet;

        return result;
    }

#endif /* XMAT4X4_DEFINITION */

#endif /* __XMAT_H__ */