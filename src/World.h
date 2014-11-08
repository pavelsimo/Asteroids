#ifndef __WORLD_H_
#define __WORLD_H_

#include <list>

#include "Drawing.h"
#include "Player.h"
#include "Bullet.h"
#include "AsteroidFactory.h"
#include "Asteroid.h"

namespace asteroids {

    typedef std::list<Asteroid*> AsteroidList;
    typedef std::list<Bullet*> BulletList;

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
            // Asteroids
            void RenderAsteroids();
            void UpdateAsteroids();
            void CreateAsteroids(AsteroidSize size, int numAsteroids);
            void CreateAsteroidDebris(const Asteroid &asteroid);
            // Bullets
            void RenderBullets();
            void UpdateBullets();
            void CleanBullets();
            void ResolveBulletsCollisions();
            // Player
            void ResolvePlayerCollisions();
            void CreatePlayerDebris();
            void RespawnPlayer();

            Player m_player;
            AsteroidFactory m_asteroidFactory;
            AsteroidList m_asteroids;
            BulletList m_bullets;
            float m_width;
            float m_height;
    };
}

#endif //__WORLD_H_
