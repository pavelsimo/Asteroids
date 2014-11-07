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
            virtual void OnUpdate(World &world) override;
            bool CanDelete() const;

        private:
            void InitializeGeometry();
            int m_lifeSpan;
    };

}

#endif //__BULLET_H_
