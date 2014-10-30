#include "AABB2.h"

AABB2::AABB2()
{
    this->Empty();
}

AABB2::AABB2(const Vector2& _min, const Vector2& _max) :
  min(_min),
  max(_max)
{

}

AABB2::AABB2(const Vector2& center, const real radius) :
    min(Vector2(center.x - fabs(radius), center.y - fabs(radius))),
    max(Vector2(center.x + radius, center.y + radius))
{

}

AABB2::~AABB2()
{

}

void AABB2::Empty()
{
    min.x = std::numeric_limits<real>::max();
    min.y = std::numeric_limits<real>::max();
    max.x = std::numeric_limits<real>::lowest();
    max.y = std::numeric_limits<real>::lowest();
}

AABB2& AABB2::Add(const Vector2 &rhs)
{
    if(rhs.x < min.x) min.x = rhs.x;
    if(rhs.y < min.y) min.y = rhs.y;
    if(rhs.x > max.x) max.x = rhs.x;
    if(rhs.y > max.y) max.y = rhs.y;
    return *this;
}

AABB2& AABB2::Move(const Vector2 &rhs)
{
    min += rhs;
    max += rhs;
    return *this;
}

AABB2& AABB2::Enlarge(const real displacement)
{
    min = min - displacement;
    max = max + displacement;
    return *this;
}

bool AABB2::IsInside(const Vector2& rhs)
{
    return !((rhs.x < min.x)
          || (rhs.y < min.y)
          || (rhs.x > max.x)
          || (rhs.y > max.y));
}

bool AABB2::Intersects(const AABB2& aabb2)
{
    return ( max.x > aabb2.min.x )
        && ( min.x < aabb2.max.x )
        && ( max.y > aabb2.min.y )
        && ( min.y < aabb2.max.y );
}

Vector2 AABB2::GetMax() const
{
    return max;
}

Vector2 AABB2::GetMin() const
{
    return min;
}

Vector2 AABB2::GetCenter() const
{
    // center point
    return (GetMin() + GetMax()) * 0.5f;
}

Vector2 AABB2::GetSize() const
{
    // size vector
    return (GetMax() - GetMin());
}

Vector2 AABB2::GetRadius() const
{
    // radius vector
    return (this->GetSize()) * 0.5f;
}

real AABB2::GetWidth() const
{
    return max.x - min.x;
}

real AABB2::GetHeight() const
{
    return max.y - min.y;
}

