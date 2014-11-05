#include "MathUtilities.h"



int32 ToNearestInt(real x)
{
    return static_cast<int32>(x + 0.5);
}

real ToRadians(real degrees)
{
    return degrees * (PI / 180.0);
}

real ToDegrees(real rad)
{
    return rad * (180.0 / PI);
}

boolean IsPowerOf2(int32 x)
{
    if(x < 0) return false;
    return !((x - 1) & x);
}

real CalcAngularDistanceInDegrees(real angle1InRadians, real angle2InRadians)
{
    real angle = fmodf(fabs(angle1InRadians - angle2InRadians), 360);
    if (angle > 180) // normalize angles
        angle = 360 - angle;
    return angle;
}

real CalcAngularDistanceInRadians(real angle1InDegrees, real angle2InDegrees)
{
    real angle = CalcAngularDistanceInDegrees(
        ToDegrees(angle1InDegrees),
        ToDegrees(angle2InDegrees)
    );
    return ToRadians(angle);
}

boolean IsNear(real lhs, real rhs, real epsilon)
{
    return fabs(lhs - rhs) < epsilon;
}

