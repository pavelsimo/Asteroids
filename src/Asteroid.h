#ifndef __ASTEROID_H_
#define __ASTEROID_H_

#include "Actor.h"
#include "Drawing.h"
#include "MathUtilities.h"

namespace asteroids
{
    enum AsteroidSize
    {
        SMALL = 1,
        MEDIUM = 2,
        BIG = 4
    };

    class World;

    class Asteroid : public Actor
    {
        public:
            Asteroid(float radius, int numVertices, float speed = 2.f);
            ~Asteroid();
            virtual void OnRender() override;
            virtual void OnUpdate(World &world) override;
            AsteroidSize GetSize() const;
            void SetSize(AsteroidSize type);

        private:
            float m_angle;
            float m_radius;
            float m_speed;
            int m_numVertices;
            AsteroidSize m_size;
            void Initialize();
    };
}

#endif //__ASTEROID_H_
