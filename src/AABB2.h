#ifndef __AABB2_H_
#define __AABB2_H_

#include "Vector2.h"
#include "MathUtilities.h"
#include <limits>

/**
* Axis Aligned Bounding Box 2D (AABB2).
*/
class AABB2
{
    public:
        // ctor & dtor
        AABB2();
        AABB2(const Vector2& min, const Vector2& max);
        AABB2(const Vector2& center, const real radius);
        ~AABB2();

        // functions
        void Empty();
        AABB2& Add(const Vector2 &rhs);
        AABB2& Move(const Vector2 &rhs);
        AABB2& Enlarge(const real displacement);
        bool IsInside(const Vector2& rhs);
        bool Intersects(const AABB2& aabb2);
        Vector2 GetMax() const;
        Vector2 GetMin() const;
        Vector2 GetCenter() const;
        Vector2 GetSize() const;
        Vector2 GetRadius() const;
        real GetWidth() const;
        real GetHeight() const;

        // properties
        Vector2 min;
        Vector2 max;
};

#endif // __AABB2_H_
