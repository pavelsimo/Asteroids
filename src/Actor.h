#ifndef __ACTOR_H_
#define __ACTOR_H_

#include <vector>

#include "Vector2.h"
#include "AABB2.h"

namespace asteroids
{
    typedef std::vector<Vector2> PointList;

    class World;

    class Actor
    {
        public:
            // ctor & dtor
            Actor();
            virtual ~Actor();

            // functions
            void Render();
            virtual void OnRender();
            void Update(World &world);
            virtual void OnUpdate(World &world);
            void MoveForward();
            virtual void OnMoveForward();
            void MoveBackward();
            virtual void OnMoveBackward();
            void RotateCW();
            virtual void OnRotateCW();
            void RotateCCW();
            virtual void OnRotateCCW();
            bool IsColliding(const Actor &actor);

            // setters & getters
            void SetPosition(const Vector2 &position);
            void SetVel(const Vector2 &vel);
            void SetDirection(const Vector2 &direction);
            void SetPoints(const PointList &points);
            Vector2 GetVel() const;
            Vector2 GetPosition() const;
            Vector2 GetDirection() const;
            AABB2 GetAABB2() const;
            const PointList &GetPoints() const;

        protected:
            Vector2 m_position;
            Vector2 m_vel;
            Vector2 m_direction;
            PointList m_points;

        private:
            AABB2 m_aabb2;
    };

}

#endif //__ACTOR_H_

