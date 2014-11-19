#ifndef __WORLD_H_
#define __WORLD_H_

#include <list>

#include "Drawing.h"
#include "Player.h"
#include "EnemyShip.h"
#include "Bullet.h"
#include "AsteroidFactory.h"
#include "Asteroid.h"
#include "SoundManager.h"

// TODO: (Pavel) Add Sound Manager Class, http://www.ogre3d.org/tikiwiki/tiki-index.php?page=OpenAl+Soundmanager

namespace asteroids
{

    typedef std::list<Asteroid*> AsteroidList;
    typedef std::list<Bullet*> BulletList;

    enum GameState
    {
        MENU,
        PLAYING,
        RESPAWN
    };

    struct AsteroidWave
    {
        int id;
        int speed;
        bool isDone;
    };

    class World {
        public:
            World(const float width, const float height);
            ~World();

            bool LoadResources();

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
            void DeleteResources();

            // Asteroids
            //
            void RenderAsteroids();
            void UpdateAsteroids();
            void CreateAsteroids(int n, AsteroidSize size, int speed);
            void CreateAsteroidsWave();
            void CreateAsteroidDebris(const Asteroid &asteroid);
            void DeleteAllAsteroids();

            // Bullets
            //
            void RenderBullets();
            void UpdateBullets();
            void DeleteFarAwayBullets();
            void DeleteAllBullets();

            // EnemyShip
            //
            void UpdateEnemyShip();
            void RenderEnemyShip();
            void DeleteEnemyShip();
            void RespawnEnemyShip();

            // Player
            //
            void UpdatePlayer();
            void RenderPlayer();
            void RenderPlayerScore();
            void DeletePlayer();
            void CreatePlayerDebris();
            void RespawnPlayer();

            // Collisions
            //
            void ResolvePlayerAsteroidCollisions();
            void ResolvePlayerBulletCollisions();
            void ResolveAsteroidBulletCollisions();
            void ResolveEnemyShipBulletCollisions();

            // Sound
            //
            SoundManager* m_soundManager;
            unsigned int m_soundShoot;
            unsigned int m_soundThrust;
            unsigned int m_soundBangBig;

            // Wave
            //
            AsteroidWave m_asteroidWave;

            GameState m_state;
            Player* m_player;
            EnemyShip* m_enemyShip;
            BitmapFont* m_bitmapFont;
            AsteroidFactory m_asteroidFactory;
            AsteroidList m_asteroids;
            BulletList m_bullets;

            float m_width;
            float m_height;
            int m_playerRespawnWait;
            int m_enemyShipRespawnWait;
    };
}

#endif //__WORLD_H_
