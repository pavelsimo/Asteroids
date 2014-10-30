#ifndef __ACTOR_H_
#define __ACTOR_H_

#include <vector>

#include "Vector2.h"
#include "AABB2.h"

class World;

typedef std::vector<Vector2> PointList;

class Actor {
    public:
        // ctor & dtor
        Actor();
        virtual ~Actor();

        // functions
        void Render();
        void Update(const World& world);
        virtual void OnRender();
        virtual void OnUpdate(const World& world);
        bool IsColliding(const Actor& actor);

        // setters & getters
        void SetPosition(const Vector2& position);
        void SetVel(const Vector2& vel);
        void SetDirection(const Vector2& direction);
        void SetPoints(const PointList& points);
        Vector2 GetVel() const;
        Vector2 GetPosition() const;
        Vector2 GetDirection() const;
        AABB2 GetAABB2() const;
        const PointList& GetPoints() const;

    protected:
        Vector2 m_position;
        Vector2 m_vel;
        Vector2 m_direction;
        PointList m_points;

    private:
        AABB2 m_aabb2;
};

#endif //__ACTOR_H_

