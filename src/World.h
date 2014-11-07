#ifndef __WORLD_H_
#define __WORLD_H_

#include <list>

#include "Drawing.h"
#include "Player.h"
#include "Bullet.h"
#include "AsteroidFactory.h"
#include "Asteroid.h"

namespace asteroids {

    class World {
        public:
            World(const float width, const float height);
            ~World();

            void Render();
            void Update();
            void OnKeyDown(unsigned char key);
            void OnKeyUp(unsigned char key);
            void OnMouseMove(int x, int y);
            void OnMouseClick(int button, int state, int x, int y);
            float GetWidth() const;
            float GetHeight() const;
            float GetLeft() const;
            float GetRight() const;
            float GetBottom() const;
            float GetTop() const;
            void AddBullet(Bullet* bullet);

        private:
            void RenderAsteroids();
            void UpdateAsteroids();
            void RenderBullets();
            void UpdateBullets();
            void CleanBullets();

            Player m_player;
            AsteroidFactory m_asteroidFactory;
            std::list<Asteroid*> m_asteroids;
            std::list<Bullet*> m_bullets;
            float m_width;
            float m_height;
    };
}

#endif //__WORLD_H_
