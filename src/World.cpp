#include <iostream>
#include <algorithm>

#include "World.h"

namespace asteroids
{
    const int WORLD_BLINK_RATE = 12;
    const int WORLD_ENEMYSHIP_RESPAWN_WAIT = 500;
    const int WORLD_PLAYER_RESPAWN_WAIT = 100;
    const int WORLD_ASTEROID_MAX_SPEED = 4;

    World::World(const float width, const float height)
    {
        m_width = width;
        m_height = height;
        m_state = GameState::PLAYING;
        m_playerRespawnWait = WORLD_PLAYER_RESPAWN_WAIT;
        m_enemyShipRespawnWait = WORLD_ENEMYSHIP_RESPAWN_WAIT;

        // Resources
        m_bitmapFont = nullptr;

        // Wave
        m_waveId = 1;
        m_waveAsteroidSpeed = 1;
        m_canStartNextWave = true;

        // Player
        m_player = new Player();
        m_player->SetPosition(Vector2(width * 0.5f, height * 0.5f));

        // Random Seed
        srand(time(NULL));
    }

    World::~World()
    {
        DeletePlayer();
        DeleteEnemyShip();
        DeleteAllBullets();
        DeleteAllAsteroids();
        DeleteResources();
    }

    bool World::LoadResources()
    {
        if(m_bitmapFont == nullptr)
        {
            m_bitmapFont = new BitmapFont();
            m_bitmapFont->LoadBitmap("/home/pavelsimo/workspace/Games_Cpp/Asteroids/fonts/vector_battle_regular_20.png");
            m_bitmapFont->LoadGlyphsFromXML("/home/pavelsimo/workspace/Games_Cpp/Asteroids/fonts/vector_battle_regular_20.xml");
            return true;
        }
        return false;
    }

    void World::DeleteResources()
    {
        if(m_bitmapFont != nullptr)
        {
            delete m_bitmapFont;
            m_bitmapFont = nullptr;
        }
    }

    void World::Render()
    {

        DrawText(m_width * 0.5f - 200, m_height * 0.5f, "Will you marry me xiong!", m_bitmapFont);


        switch (m_state)
        {
            case GameState::RESPAWN:
                // BLINK
                if(m_playerRespawnWait % WORLD_BLINK_RATE == 0)
                {
                    RenderPlayer();
                }
                RenderEnemyShip();
                RenderAsteroids();
                RenderBullets();
                break;
            case GameState::PLAYING:
                RenderPlayer();
                RenderEnemyShip();
                RenderAsteroids();
                RenderBullets();
                break;
        }
    }

    void World::Update()
    {
        CreateAsteroidsWave();

        switch (m_state)
        {
            case GameState::RESPAWN:
                if(!m_playerRespawnWait)
                {
                    m_state = GameState::PLAYING;
                }
                UpdatePlayer();
                UpdateEnemyShip();
                UpdateAsteroids();
                UpdateBullets();
                DeleteFarAwayBullets();
                RespawnEnemyShip();
                ResolveAsteroidBulletCollisions();
                ResolveEnemyShipBulletCollisions();
                m_playerRespawnWait = std::max(0, m_playerRespawnWait - 1);
                break;
            case GameState::PLAYING:
                UpdatePlayer();
                UpdateEnemyShip();
                UpdateAsteroids();
                UpdateBullets();
                DeleteFarAwayBullets();
                RespawnEnemyShip();
                ResolveAsteroidBulletCollisions();
                ResolvePlayerAsteroidCollisions();
                ResolvePlayerBulletCollisions();
                ResolveEnemyShipBulletCollisions();
                break;
        }
    }

    void World::OnKeyDown(unsigned char key)
    {
        switch(key)
        {
            case 'w':
            case 'W':
                m_player->AddState(PlayerState::MOVING_FORWARD);
            break;
            case 's':
            case 'S':
                m_player->AddState(PlayerState::MOVING_BACKWARD);
            break;
            case 'a':
            case 'A':
                m_player->AddState(PlayerState::ROTATING_CCW);
            break;
            case 'd':
            case 'D':
                m_player->AddState(PlayerState::ROTATING_CW);
            break;
            case ' ':
                m_player->AddState(PlayerState::SHOOTING);
            break;
        }
    }

    void World::OnKeyUp(unsigned char key)
    {
        switch(key)
        {
            case 'w':
            case 'W':
                m_player->RemoveState(PlayerState::MOVING_FORWARD);
                break;
            case 's':
            case 'S':
                m_player->RemoveState(PlayerState::MOVING_BACKWARD);
                break;
            case 'a':
            case 'A':
                m_player->RemoveState(PlayerState::ROTATING_CCW);
                break;
            case 'd':
            case 'D':
                m_player->RemoveState(PlayerState::ROTATING_CW);
                break;
            case ' ':
                m_player->RemoveState(PlayerState::SHOOTING);
            break;
        }
    }

    void World::OnMouseMove(int x, int y)
    {

    }

    void World::OnMouseClick(int button, int state, int x, int y)
    {

    }

    float World::GetWidth() const
    {
        return m_width;
    }

    float World::GetHeight() const
    {
        return m_height;
    }

    float World::GetLeft() const
    {
        return 0;
    }

    float World::GetRight() const
    {
        return m_width;
    }

    float World::GetBottom() const
    {
        return m_height;
    }

    float World::GetTop() const
    {
        return 0;
    }

    void World::RenderBullets()
    {
        for(auto it = m_bullets.begin(); it != m_bullets.end(); it++)
        {
            (*it)->Render();
        }
    }

    void World::UpdateBullets()
    {
        for(auto it = m_bullets.begin(); it != m_bullets.end(); it++)
        {
            (*it)->Update(*this);
        }
    }

    void World::DeleteFarAwayBullets()
    {
        for(auto it = m_bullets.begin(); it != m_bullets.end(); it++)
        {
            Bullet* bullet = *it;
            if(bullet->CanDelete())
            {
                it = m_bullets.erase(it);
                delete bullet;
            }
        }
    }

    void World::AddBullet(Bullet* bullet)
    {
        m_bullets.push_back(bullet);
    }

    void World::RenderAsteroids()
    {
        for(auto it = m_asteroids.begin(); it != m_asteroids.end(); it++)
        {
            (*it)->Render();
        }
    }

    void World::UpdateAsteroids()
    {
        for(auto it = m_asteroids.begin(); it != m_asteroids.end(); it++)
        {
            (*it)->Update(*this);
        }
    }

    void World::CreateAsteroidDebris(const Asteroid &asteroid)
    {
        AsteroidSize size = asteroid.GetSize();
        int numAsteroids = 2;

        switch(size)
        {
            case AsteroidSize::BIG:
                for(int i = 0; i < numAsteroids; ++i)
                {
                    Asteroid* mediumAsteroid = m_asteroidFactory.CreateMediumAsteroid(m_waveAsteroidSpeed);
                    mediumAsteroid->SetPosition(asteroid.GetPosition());
                    m_asteroids.push_back(mediumAsteroid);
                }
            break;
            case AsteroidSize::MEDIUM:
                for(int i = 0; i < numAsteroids; ++i)
                {
                    Asteroid* smallAsteroid = m_asteroidFactory.CreateSmallAsteroid(m_waveAsteroidSpeed);
                    smallAsteroid->SetPosition(asteroid.GetPosition());
                    m_asteroids.push_back(smallAsteroid);
                }
            break;
        }
    }

    void World::ResolvePlayerAsteroidCollisions()
    {
        // TODO: (Pavel) Add a common method for this and ResolvePlayerBulletCollisions()
        for(auto i = m_asteroids.begin(); i != m_asteroids.end(); i++)
        {
            Asteroid* asteroid = *i;
            if(m_player->IsColliding(*asteroid))
            {
                CreatePlayerDebris();
                RespawnPlayer();
                break;
            }
        }
    }

    void World::ResolvePlayerBulletCollisions()
    {
        // TODO: (Pavel) Add a common method for this and ResolvePlayerAsteroidCollisions()
        for(auto i = m_bullets.begin(); i != m_bullets.end(); i++)
        {
            Bullet* bullet = *i;
            if(m_player->IsColliding(*bullet))
            {
                CreatePlayerDebris();
                RespawnPlayer();
                break;
            }
        }
    }

    void World::ResolveEnemyShipBulletCollisions()
    {
        if(m_enemyShip != nullptr)
        {
            for(auto i = m_bullets.begin(); i != m_bullets.end(); i++)
            {
                Bullet* bullet = *i;
                if(m_enemyShip->IsColliding(*bullet))
                {
                    DeleteEnemyShip();
                    m_bullets.erase(i);
                    delete bullet;
                    break;
                }
            }
        }
    }

    void World::ResolveAsteroidBulletCollisions()
    {
        for(auto i = m_bullets.begin(); i != m_bullets.end(); i++)
        {
            Bullet* bullet = *i;
            for(auto j = m_asteroids.begin(); j != m_asteroids.end(); j++)
            {
                Asteroid* asteroid = *j;
                if(bullet->IsColliding(*asteroid))
                {
                    i = m_bullets.erase(i);
                    CreateAsteroidDebris(*asteroid);
                    m_asteroids.erase(j);
                    delete asteroid;
                    delete bullet;
                    break;
                }
            }
        }
    }

    void World::CreateAsteroids(int n, AsteroidSize size, int speed)
    {
        float w = m_width;
        float h = m_height;
        float x[] = {0, w, 0, w};
        float y[] = {0, 0, h, h};
        for(int i = 0, j = 0; i < n; ++i, ++j)
        {
            Asteroid* asteroid = m_asteroidFactory.Create(size);
            asteroid->SetPosition(Vector2(x[j], y[j]));
            m_asteroids.push_back(asteroid);
            if(j >= 4) j = 0;
        }
    }

    void World::CreatePlayerDebris()
    {
        // TODO: (Pavel) Implement CreatePlayerDebris()
    }

    void World::RespawnPlayer()
    {
        m_player->Initialize();
        m_player->SetPosition(Vector2(m_width * 0.5f, m_height * 0.5f));
        m_state = GameState::RESPAWN;
        m_playerRespawnWait = WORLD_PLAYER_RESPAWN_WAIT;
    }

    const Player& World::GetPlayer() const
    {
        return *m_player;
    }


    void World::UpdateEnemyShip()
    {
        if(m_enemyShip != nullptr)
        {
            m_enemyShip->Update(*this);
        }
    }

    void World::RenderEnemyShip()
    {
        if(m_enemyShip != nullptr)
        {
            m_enemyShip->Render();
        }
    }


    void World::RespawnEnemyShip()
    {
        if(m_enemyShip == nullptr)
        {
            if(!m_enemyShipRespawnWait)
            {
                m_enemyShip = new EnemyShip();
                m_enemyShip->SetPosition(Vector2(0, Random<int>(0, m_height)));
            }
            m_enemyShipRespawnWait = std::max(0, m_enemyShipRespawnWait - 1);
        } else {
            m_enemyShipRespawnWait = WORLD_ENEMYSHIP_RESPAWN_WAIT;
        }
    }

    void World::UpdatePlayer()
    {
        if(m_player != nullptr)
        {
            m_player->Update(*this);
        }
    }

    void World::RenderPlayer()
    {
        if(m_player != nullptr)
        {
            m_player->Render();
        }
    }

    void World::DeleteEnemyShip()
    {
        if(m_enemyShip != nullptr)
        {
            delete m_enemyShip;
            m_enemyShip = nullptr;
        }
    }

    void World::DeletePlayer()
    {
        if(m_player != nullptr)
        {
            delete m_player;
            m_player = nullptr;
        }
    }

    void World::DeleteAllAsteroids()
    {
        for(auto it = m_asteroids.begin(); it != m_asteroids.end(); it++)
        {
            if(*it != nullptr)
            {
                delete *it;
            }
        }
        m_asteroids.clear();
    }

    void World::DeleteAllBullets()
    {
        for(auto it = m_bullets.begin(); it != m_bullets.end(); it++)
        {
            if(*it != nullptr)
            {
                delete *it;
            }
        }
        m_bullets.clear();
    }

    void World::CreateAsteroidsWave()
    {
        if(m_canStartNextWave)
        {
            int numAsteroids = m_waveId * 2;
            m_waveAsteroidSpeed = std::min(m_waveId, WORLD_ASTEROID_MAX_SPEED);
            CreateAsteroids(numAsteroids, AsteroidSize::BIG, m_waveAsteroidSpeed);
            m_canStartNextWave = false;
            m_waveId++;
        }

        if(m_asteroids.empty())
        {
            m_canStartNextWave = true;
        }
    }
}