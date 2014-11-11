#include <cmath>
#include <cassert>

#include "Vector2.h"

Vector2::Vector2() :
    x(0), y(0)
{

}

Vector2::Vector2(real _x, real _y) :
    x(_x), y(_y)
{

}

Vector2::Vector2(const Vector2 &rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
}

void Vector2::Normalize()
{
    real length = this->CalcLength();
    assert(length != 0);
    this->x /= length;
    this->y /= length;
}

void Vector2::SetXY(real _x, real _y)
{
    this->x = _x;
    this->y = _y;
}

void Vector2::SetX(real _x)
{
    this->x = _x;
}

void Vector2::SetY(real _y)
{
    this->y = _y;
}

void Vector2::SetLengthAndYawRadians(
    real radius,
    real angleInRadians)
{
    this->x = radius * cos(angleInRadians);
    this->y = radius * sin(angleInRadians);
}

void Vector2::SetUnitLengthAndYawRadians(real angleInRadians)
{
    SetLengthAndYawRadians(1, angleInRadians);
}

void Vector2::SetUnitLengthAndYawDegrees(real angleInDegrees)
{
    SetLengthAndYawRadians(1, Deg2Rad(angleInDegrees));
}

void Vector2::SetLengthAndYawDegrees(
    real radius,
    real angleInDegrees)
{
    SetLengthAndYawRadians(radius, Deg2Rad(angleInDegrees));
}

void Vector2::SetLength(real radius)
{
    real angle = this->CalcYawRadians();
    SetLengthAndYawRadians(radius, angle);
}

void Vector2::ScaleUniform(real unit)
{
    this->x *= unit;
    this->y *= unit;
}

void Vector2::ScaleX(real unit)
{
    this->x *= unit;
}

void Vector2::ScaleY(real unit)
{
    this->y *= unit;
}

Vector2& Vector2::RotateRadians(real angleInRadians)
{
    real cosangle = cos(angleInRadians);
    real sinangle = sin(angleInRadians);
    real n_x = this->x * cosangle - this->y * sinangle;
    real n_y = this->y * cosangle + this->x * sinangle;
    this->x = n_x;
    this->y = n_y;
    return *this;
}

Vector2& Vector2::RotateDegrees(real angleInDegrees)
{
    return RotateRadians(Deg2Rad(angleInDegrees));
}

Vector2& Vector2::Rotate90Degrees()
{
    return RotateRadians(Deg2Rad(90));
}

Vector2& Vector2::RotateMinus90Degrees()
{
    return RotateRadians(Deg2Rad(-90));
}

Vector2& Vector2::Reverse()
{
    // swap
    real tmp = this->x;
    this->x = this->y;
    this->y = tmp;
    return *this;
}

void Vector2::GetXY( real& _x, real& _y )
{
    _x = this->x;
    _y = this->y;
}

real Vector2::GetX() const
{
    return this->x;
}

real Vector2::GetY() const
{
    return this->y;
}

real Vector2::CalcLength() const
{
    return sqrt(this->CalcLengthSquared());
}

real Vector2::CalcLengthSquared() const
{
    return this->x * this->x + this->y * this->y;
}

real Vector2::DotProduct(const Vector2 &rhs) const
{
    return this->x * rhs.x + this->y * rhs.y;
}

real Vector2::CalcYawRadians() const
{
    return atan2(this->y, this->x);
}

real Vector2::CalcYawDegrees() const
{
    return Rad2Deg(this->CalcYawRadians());
}

Vector2 & Vector2::operator=(const Vector2 &rhs)
{
    if ( this == &rhs ) {
        return *this;
    }
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

Vector2 & Vector2::operator+=(const Vector2 &rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vector2 & Vector2::operator-=(const Vector2 &rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vector2 & Vector2::operator*=(real unit)
{
    this->x *= unit;
    this->y *= unit;
    return *this;
}

Vector2 & Vector2::operator/=(real unit)
{
    assert(unit != 0);
    this->x /= unit;
    this->y /= unit;
    return *this;
}

Vector2 Vector2::operator+(const Vector2 &rhs)
{
    return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2 Vector2::operator+(const real displacement)
{
    Vector2 res;
    res.x = x + displacement;
    res.y = y + displacement;
    return res;
}

Vector2 Vector2::operator-(const Vector2 &rhs)
{
    return Vector2(this->x - rhs.x, this->y - rhs.y);
}

Vector2 Vector2::operator-(const real displacement)
{
    Vector2 res;
    res.x = x - displacement;
    res.y = y - displacement;
    return res;
}

Vector2 Vector2::operator*(real unit)
{
    return Vector2(this->x * unit, this->y * unit);
}

Vector2 Vector2::operator/(real unit)
{
    assert(unit != 0);
    return Vector2(this->x / unit, this->y / unit);
}

Vector2 Vector2::operator-()
{
    return Vector2(-this->x, -this->y);
}

bool Vector2::operator==(const Vector2 &rhs)
{
    return IsApproximately(this->x, rhs.x) && IsApproximately(this->y, rhs.y);
}

bool Vector2::operator!=(const Vector2 &rhs)
{
    return !(*this == rhs);
}

Vector2 operator*(real unit, const Vector2& rhs)
{
    return Vector2(unit * rhs.x, unit * rhs.y);
}
