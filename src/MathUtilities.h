#ifndef __MATH_UTILITIES_H_
#define __MATH_UTILITIES_H_

#include <cmath>
#include <cstdint>
#include <cstdlib>

typedef float real;
typedef int32_t int32;
typedef bool boolean;

const real EPS = 1e-6;
const real PI = 3.14159265358979f;

int32 RoundToInt(real x);

template <typename T>
T Clamp(T x, T lo, T hi)
{
    if(hi < lo) {
        T tmp = lo;
        lo = hi;
        hi = tmp;
    }
    if(x < lo) x = lo;
    if(x > hi) x = hi;
    return x;
}

/*
    // Precise method
    http://en.wikipedia.org/wiki/Linear_int32erpolation

    lo + t * (hi - lo)
    lo + t * hi - t * lo
    (lo - t * lo) + t * hi
    (1 - t) * lo + t * hi
*/
template <typename T>
T Lerp(T const &lo, T const &hi, real t)
{
    return (1 - t) * lo + t * hi;
}

template <typename T>
T Random(T lo, T hi)
{
    return lo + (rand() % (hi - lo + 1));
}

real Rad2Deg(real radians);

real Deg2Rad(real degrees);

real CalcAngularDistanceInRadians(real angle1InRadians, real angle2InRadians);

real CalcAngularDistanceInDegrees(real angle1InDegrees, real angle2InDegrees);

boolean IsPowerOf2(int32 x);

boolean IsApproximately(real lhs, real rhs, real epsilon = 0.001);


#endif // __MATH_UTILITIES_H_
