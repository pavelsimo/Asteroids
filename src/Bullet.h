#ifndef __BULLET_H_
#define __BULLET_H_

#include "Actor.h"
#include "Drawing.h"

namespace asteroids
{
    class World;

    class Bullet : public Actor {
        public:
            Bullet();
            ~Bullet();
            virtual void OnRender() override;
            virtual void OnUpdate(const World &world) override;

        private:
            void InitializeGeometry();
    };

}

#endif //__BULLET_H_
