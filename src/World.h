#ifndef __WORLD_H_
#define __WORLD_H_

#include <list>
#include <chrono>

#include "Drawing.h"
#include "Player.h"
#include "EnemyShip.h"
#include "Bullet.h"
#include "AsteroidFactory.h"
#include "Asteroid.h"

namespace asteroids {

    typedef std::list<Asteroid*> AsteroidList;
    typedef std::list<Bullet*> BulletList;

    enum GameState
    {
        PLAYING,
        RESPAWN
    };

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
            const Player& GetPlayer() const;

        private:
            // Asteroids
            void RenderAsteroids();
            void UpdateAsteroids();
            void CreateAsteroids(int n, AsteroidSize size, int speed);
            void CreateAsteroidsWave();
            void CreateAsteroidDebris(const Asteroid &asteroid);
            void DeleteAllAsteroids();

            // Bullets
            void RenderBullets();
            void UpdateBullets();
            void DeleteFarAwayBullets();
            void DeleteAllBullets();

            // EnemyShip
            void UpdateEnemyShip();
            void RenderEnemyShip();
            void DeleteEnemyShip();

            // Player
            void UpdatePlayer();
            void RenderPlayer();
            void DeletePlayer();
            void CreatePlayerDebris();
            void RespawnPlayer();

            // Collisions
            void ResolvePlayerAsteroidCollisions();
            void ResolvePlayerBulletCollisions();
            void ResolveAsteroidBulletCollisions();
            void ResolveEnemyShipBulletCollisions();

            GameState m_state;
            int m_playerRespawnWait;
            Player *m_player;
            EnemyShip *m_enemyShip;
            AsteroidFactory m_asteroidFactory;
            AsteroidList m_asteroids;
            BulletList m_bullets;
            int m_waveId;
            int m_waveAsteroidSpeed;
            bool m_startNextWave;
            float m_width;
            float m_height;
    };
}

#endif //__WORLD_H_
