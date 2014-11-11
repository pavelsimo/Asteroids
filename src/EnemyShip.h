#ifndef __ENEMYSHIP_H_
#define __ENEMYSHIP_H_

#include "LOpenGL.h"
#include "Actor.h"
#include "Vector2.h"
#include "Bullet.h"

namespace asteroids
{
    class World;

    class EnemyShip : public Actor
    {
        public:
            EnemyShip();
            ~EnemyShip();

            virtual void OnRender() override;
            virtual void OnUpdate(World &world) override;
            void Shoot(World &world);

        private:
            void InitializeGeometry();
            int m_shootTimeout;
    };
}

#endif //__ENEMYSHIP_H_
