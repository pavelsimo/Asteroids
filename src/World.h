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

namespace asteroids
{
    typedef std::list<Actor*> ActorList;

    enum GameState
    {
        MENU,
        PLAYING,
        RESPAWN,
        GAMEOVER
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
            void Restart();

            // Events
            //
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
            SoundManager& GetSoundManager();

            // Sounds
            //
            unsigned int SOUND_FIRE;
            unsigned int SOUND_THRUST;
            unsigned int SOUND_BIG_ASTEROID_BANG;
            unsigned int SOUND_MEDIUM_ASTEROID_BANG;
            unsigned int SOUND_SMALL_ASTEROID_BANG;

        private:
            // Game
            //
            GameState m_state;
            float m_width;
            float m_height;

            // Actors
            //
            Player* m_player;
            EnemyShip* m_enemyShip;
            ActorList m_asteroids;
            ActorList m_bullets;
            AsteroidFactory m_asteroidFactory;
            int m_playerRespawnWait;
            int m_enemyShipRespawnWait;

            // Resources
            //
            BitmapFont* m_bitmapFont;
            SoundManager* m_soundManager;

            // Wave
            //
            AsteroidWave m_asteroidWave;

            // Asteroids
            //
            void RenderAsteroids();
            void UpdateAsteroids();
            void CreateAsteroids(int n, AsteroidSize size, int speed);
            void CreateAsteroidsWave();
            void CreateAsteroidDebris(const Asteroid& asteroid);
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
            void RenderPlayerLifes();
            void DeletePlayer();
            void CreatePlayerDebris();
            void RespawnPlayer();


            // Collisions
            //
            void ResolvePlayerActorCollisions(const ActorList& actors);
            void ResolvePlayerAsteroidCollisions();
            void ResolvePlayerBulletCollisions();
            void ResolveAsteroidBulletCollisions();
            void ResolveEnemyShipBulletCollisions();

            // Resources
            //
            void DeleteResources();
    };
}

#endif //__WORLD_H_
