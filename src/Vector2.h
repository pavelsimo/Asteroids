#ifndef __VECTOR2_H_
#define __VECTOR2_H_

#include "MathUtilities.h"

class Vector2
{
    public:
        // constructors
        Vector2();
        Vector2(real x, real y);
        Vector2(const Vector2 &rhs);

        // functions
        void Normalize();
        void SetXY(real x, real y);
        void SetX(real x);
        void SetY(real y);
        void SetUnitLengthAndYawRadians(real angleInRadians);
        void SetUnitLengthAndYawDegrees(real angleInDegrees);
        void SetLengthAndYawRadians(real radius, real angleInRadians);
        void SetLengthAndYawDegrees(real radius, real angleInDegrees);
        void SetLength(real radius);
        void ScaleUniform(real unit);
        void ScaleX(real unit);
        void ScaleY(real unit);
        Vector2& RotateDegrees(real angleInDegrees);
        Vector2& RotateRadians(real angleInRadians);
        Vector2& Rotate90Degrees();
        Vector2& RotateMinus90Degrees();
        Vector2& Reverse();
        void GetXY( real& x, real& y );
        real GetX() const;
        real GetY() const;
        real CalcLength() const;
        real CalcLengthSquared() const;
        real CalcYawRadians() const;
        real CalcYawDegrees() const;
        real DotProduct(const Vector2 &rhs) const;

        // operators
        Vector2& operator=(const Vector2 &rhs);
        Vector2& operator+=(const Vector2 &rhs);
        Vector2& operator-=(const Vector2 &rhs);
        Vector2& operator*=(real unit);
        Vector2& operator/=(real unit);
        Vector2 operator+(const Vector2 &rhs);
        Vector2 operator+(const real displacement);
        Vector2 operator-(const Vector2 &rhs);
        Vector2 operator-(const real displacement);
        Vector2 operator*(real unit);
        Vector2 operator/(real unit);
        Vector2 operator-();
        bool operator==(const Vector2 &rhs);
        bool operator!=(const Vector2 &rhs);
        friend Vector2 operator*(real unit, const Vector2& rhs);

        real x;
        real y;
};

#endif // __VECTOR2_H_
