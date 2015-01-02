#include <iostream>
#include <algorithm>
#include <string>

#include "World.h"

namespace asteroids
{
    // Player
    //
    const int PLAYER_LIFES = 3;
    const int PLAYER_BLINK_RATE = 12;
    const int PLAYER_RESPAWN_WAIT = 100;
    const int PLAYER_DESTROY_ASTEROID_PTS = 20;
    const int PLAYER_DESTROY_ENEMYSHIP_PTS = 100;

    // Asteroids
    //
    const int ASTEROID_MAX_SPEED = 4;

    // Enemy Ships
    //
    const int ENEMYSHIP_RESPAWN_WAIT = 500;

    // Fonts
    //
    const std::string FONT_BITMAP = "fonts/hyperspace_bold_65.png";
    const std::string FONT_CONFIG = "fonts/hyperspace_bold_65.xml";

    // Sounds
    //
    const std::string SOUND_FIRE_SRC = "sounds/fire.wav";
    const std::string SOUND_THRUST_SRC = "sounds/thrust.wav";
    const std::string SOUND_BIG_ASTEROID_BANG_SRC = "sounds/bangLarge.wav";
    const std::string SOUND_MEDIUM_ASTEROID_BANG_SRC = "sounds/bangMedium.wav";
    const std::string SOUND_SMALL_ASTEROID_BANG_SRC = "sounds/bangSmall.wav";

    World::World(const float width, const float height)
    {
        m_width = width;
        m_height = height;
        m_state = GameState::MENU;
        m_playerRespawnWait = PLAYER_RESPAWN_WAIT;

        // Player
        //
        m_player = new Player();
        m_player->SetPosition(Vector2(m_width * 0.5f, m_height * 0.5f));
        m_player->SetLifes(PLAYER_LIFES);
        m_player->SetScore(0);

        // Enemy Ship
        //
        m_enemyShip = nullptr;
        m_enemyShipRespawnWait = ENEMYSHIP_RESPAWN_WAIT;

        // Resources
        //
        m_bitmapFont = nullptr;
        m_soundManager = nullptr;

        // Wave
        //
        m_asteroidWave.id = 1;
        m_asteroidWave.speed = 1;
        m_asteroidWave.isDone = true;

        // Random Seed
#ifdef _WIN32
        srand(time_t(NULL));
#else
        srand(time(NULL));
#endif
    }

    World::~World()
    {
        DeletePlayer();
        DeleteEnemyShip();
        DeleteAllBullets();
        DeleteAllAsteroids();
        DeleteResources();
    }

    void World::Restart()
    {
        DeleteEnemyShip();
        DeleteAllBullets();
        DeleteAllAsteroids();
        m_player->SetPosition(Vector2(m_width * 0.5f, m_height * 0.5f));
        m_player->SetLifes(PLAYER_LIFES);
        m_player->SetScore(0);
        m_asteroidWave.id = 1;
        m_asteroidWave.speed = 1;
        m_asteroidWave.isDone = true;
        m_state = GameState::PLAYING;
    }

    bool World::LoadResources()
    {
        if(m_bitmapFont == nullptr)
        {
            m_bitmapFont = new BitmapFont();
            m_bitmapFont->LoadBitmap(FONT_BITMAP);
            m_bitmapFont->LoadGlyphsFromXML(FONT_CONFIG);
        }

        if(m_soundManager == nullptr)
        {
            m_soundManager = SoundManager::Instance();
            m_soundManager->Initialize();

            m_soundManager->LoadAudio(
                SOUND_FIRE_SRC,
                &SOUND_FIRE,
                false
            );

            m_soundManager->LoadAudio(
                SOUND_THRUST_SRC,
                &SOUND_THRUST,
                true
            );

            m_soundManager->LoadAudio(
                SOUND_BIG_ASTEROID_BANG_SRC,
                &SOUND_BIG_ASTEROID_BANG,
                false
            );

            m_soundManager->LoadAudio(
                SOUND_MEDIUM_ASTEROID_BANG_SRC,
                &SOUND_MEDIUM_ASTEROID_BANG,
                false
            );

            m_soundManager->LoadAudio(
                SOUND_SMALL_ASTEROID_BANG_SRC,
                &SOUND_SMALL_ASTEROID_BANG,
                false
            );
        }
        return true;
    }

    void World::DeleteResources()
    {
        if(m_bitmapFont != nullptr)
        {
            delete m_bitmapFont;
            m_bitmapFont = nullptr;
        }
        if(m_soundManager != nullptr)
        {
            delete m_soundManager;
            m_soundManager = nullptr;
        }
    }

    void World::Render()
    {
        std::string gameOver = "Game Over";
        std::string asteroid = "Asteroid";

        switch (m_state)
        {
            case GameState::GAMEOVER:
                RenderAsteroids();
                DrawText(
                    m_width * 0.5f - 55*4,
                    m_height * 0.5f - 55,
                    gameOver,
                    m_bitmapFont
                );
                break;
            case GameState::MENU:
                DrawText(
                    m_width * 0.5f - 55*3,
                    m_height * 0.5f - 55,
                    asteroid,
                    m_bitmapFont
                );
                break;
            case GameState::RESPAWN:
                // BLINK
                RenderPlayerScore();
                RenderPlayerLifes();
                if(m_playerRespawnWait % PLAYER_BLINK_RATE == 0)
                {
                    RenderPlayer();
                }
                RenderEnemyShip();
                RenderAsteroids();
                RenderBullets();
                break;
            case GameState::PLAYING:
                RenderPlayerScore();
                RenderPlayerLifes();
                RenderPlayer();
                RenderEnemyShip();
                RenderAsteroids();
                RenderBullets();
                break;
        }
    }

    void World::Update()
    {
        switch (m_state)
        {
            case GameState::GAMEOVER:

                // Updates
                //
                UpdateAsteroids();

                break;
            case GameState::RESPAWN:

                if(!m_playerRespawnWait)
                {
                    m_state = GameState::PLAYING;
                }

                // Updates
                //
                UpdatePlayer();
                UpdateEnemyShip();
                UpdateAsteroids();
                UpdateBullets();

                // Other Actions
                //
                DeleteFarAwayBullets();
                RespawnEnemyShip();

                // Collisions
                //
                ResolveAsteroidBulletCollisions();
                ResolveEnemyShipBulletCollisions();


                m_playerRespawnWait = std::max(0, m_playerRespawnWait - 1);

                break;
            case GameState::PLAYING:

                CreateAsteroidsWave();

                // Updates
                //
                UpdatePlayer();
                UpdateEnemyShip();
                UpdateAsteroids();
                UpdateBullets();

                // Other Actions
                //
                DeleteFarAwayBullets();
                RespawnEnemyShip();

                // Collisions
                //
                ResolveAsteroidBulletCollisions();
                ResolvePlayerAsteroidCollisions();
                ResolvePlayerBulletCollisions();
                ResolveEnemyShipBulletCollisions();

                break;
        }
    }

    void World::OnKeyDown(unsigned char key)
    {
        switch (m_state)
        {
            case GameState::PLAYING:
            case GameState::RESPAWN:
                switch(key)
                {
                    case 'w':
                    case 'W':
                        m_player->AddState(PlayerState::MOVING_FORWARD);
                        m_soundManager->Play(SOUND_THRUST, true);
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
                break;
        }
    }

    void World::OnKeyUp(unsigned char key)
    {
        switch (m_state)
        {
            case GameState::PLAYING:
            case GameState::RESPAWN:
                switch(key)
                {
                    case 'w':
                    case 'W':
                        m_player->RemoveState(PlayerState::MOVING_FORWARD);
                        m_soundManager->Stop(SOUND_THRUST);
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
                break;
        }
    }

    void World::OnMouseMove(int x, int y)
    {

    }

    void World::OnMouseClick(int button, int state, int x, int y)
    {
        switch (m_state)
        {
            case GameState::MENU:
                m_state = GameState::PLAYING;
                break;
            case GameState::GAMEOVER:
                Restart();
                break;
        }
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
        for(auto it = m_bullets.begin(); it != m_bullets.end(); )
        {
            Bullet* bullet = dynamic_cast<Bullet*>(*it);
            if(bullet->CanDelete())
            {
                it = m_bullets.erase(it);
                DeleteActor(bullet);
            } else {
                it++;
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

    void World::CreateAsteroidDebris(const Asteroid& asteroid)
    {
        AsteroidSize size = asteroid.GetSize();
        int numAsteroids = 2;
        int speed = std::min(m_asteroidWave.speed + 1, ASTEROID_MAX_SPEED);
        switch(size)
        {
            case AsteroidSize::BIG:
                m_soundManager->Play(SOUND_BIG_ASTEROID_BANG, true);
                for(int i = 0; i < numAsteroids; ++i)
                {
                    Asteroid* mediumAsteroid = m_asteroidFactory.CreateMediumAsteroid((float)speed);
                    mediumAsteroid->SetPosition(asteroid.GetPosition());
                    m_asteroids.push_back(mediumAsteroid);
                }
                break;
            case AsteroidSize::MEDIUM:
                m_soundManager->Play(SOUND_MEDIUM_ASTEROID_BANG, true);
                for(int i = 0; i < numAsteroids; ++i)
                {
                    Asteroid* smallAsteroid = m_asteroidFactory.CreateSmallAsteroid((float)speed);
                    smallAsteroid->SetPosition(asteroid.GetPosition());
                    m_asteroids.push_back(smallAsteroid);
                }

                break;
            case AsteroidSize::SMALL:
                m_soundManager->Play(SOUND_SMALL_ASTEROID_BANG, true);
            break;
        }
    }


    void World::ResolvePlayerActorCollisions(const ActorList &actors)
    {
        for(auto i = actors.begin(); i != actors.end(); i++)
        {
            Actor* actor = *i;
            if(m_player->IsColliding(*actor))
            {
                CreatePlayerDebris();
                RespawnPlayer();
                break;
            }
        }
    }

    void World::ResolvePlayerAsteroidCollisions()
    {
        ResolvePlayerActorCollisions(m_asteroids);
    }

    void World::ResolvePlayerBulletCollisions()
    {
        ResolvePlayerActorCollisions(m_bullets);
    }

    void World::ResolveEnemyShipBulletCollisions()
    {
        if(m_enemyShip != nullptr)
        {
            for(auto i = m_bullets.begin(); i != m_bullets.end(); i++)
            {
                Actor* bullet = *i;
                if(m_enemyShip->IsColliding(*bullet))
                {
                    // Remove from the list
                    m_bullets.erase(i);

                    // Deallocate
                    DeleteEnemyShip();
                    DeleteActor(bullet);

                    // Increase player score
                    m_player->AddScore(PLAYER_DESTROY_ENEMYSHIP_PTS);
                    break;
                }
            }
        }
    }

    void World::ResolveAsteroidBulletCollisions()
    {
        for(auto i = m_bullets.begin(); i != m_bullets.end(); )
        {
            Bullet* bullet = dynamic_cast<Bullet*>(*i);
            Asteroid* asteroid = nullptr;
            bool foundCollision = false;

            for(auto j = m_asteroids.begin(); j != m_asteroids.end(); j++)
            {
                asteroid = dynamic_cast<Asteroid*>(*j);
                if(bullet->IsColliding(*asteroid))
                {
                    foundCollision = true;

                    // Remove from the list
                    i = m_bullets.erase(i);
                    m_asteroids.erase(j);

                    // Deallocate
                    DeleteActor(bullet);

                    // Increase player score
                    m_player->AddScore(PLAYER_DESTROY_ASTEROID_PTS);
                    break;
                }
            }
            if(!foundCollision) 
            {
                i++;
            }
            else
            {
                CreateAsteroidDebris(*asteroid);
                DeleteActor(asteroid);
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
            if(j >= 4)
            {
                j = 0;
            }
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
        m_playerRespawnWait = PLAYER_RESPAWN_WAIT;
        m_player->DecreaseOneLife();
        if(m_player->IsDead())
        {
            m_state = GameState::GAMEOVER;
            m_soundManager->StopAll();
        }
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
                m_enemyShip->SetPosition(
                    Vector2(0.f, (float) Random<int>(0, (int) m_height))
                );
            }
            m_enemyShipRespawnWait = std::max(0, m_enemyShipRespawnWait - 1);
        } else {
            m_enemyShipRespawnWait = ENEMYSHIP_RESPAWN_WAIT;
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

    void World::DeleteAllAsteroids()
    {
        for(auto it = m_asteroids.begin(); it != m_asteroids.end(); it++)
        {
            DeleteActor(*it);
        }
        m_asteroids.clear();
    }

    void World::DeleteAllBullets()
    {
        for(auto it = m_bullets.begin(); it != m_bullets.end(); it++)
        {
            DeleteActor(*it);
        }
        m_bullets.clear();
    }

    void World::CreateAsteroidsWave()
    {
        if(m_asteroidWave.isDone)
        {
            int numAsteroids = m_asteroidWave.id * 2;
            m_asteroidWave.speed = std::min(m_asteroidWave.id, ASTEROID_MAX_SPEED);
            CreateAsteroids(numAsteroids, AsteroidSize::BIG, m_asteroidWave.speed);
            m_asteroidWave.id++;
            m_asteroidWave.isDone = false;
        }

        if(m_asteroids.empty())
        {
            m_asteroidWave.isDone = true;
        }
    }

    void World::RenderPlayerScore()
    {
        int score = m_player->GetScore();
        DrawText(20.f, 20.f, std::to_string(static_cast<long long>(score)), m_bitmapFont, 0.8f);
    }

    void World::RenderPlayerLifes()
    {
        PointList pts = m_player->GetPoints();
        int lifes = m_player->GetLifes();
        int x = static_cast<int>(m_width - 100);
        int y = 40;
        for(int i = 0; i < lifes; ++i)
        {
            DrawPolygon(pts, (float)x, (float)y, 180.f);
            x += 30;
        }
    }

    SoundManager& World::GetSoundManager()
    {
        return *m_soundManager;
    }

    void World::DeleteActor(Actor *actor)
    {
        if(actor != nullptr)
        {
            delete actor;
        }
    }

    void World::DeletePlayer()
    {
        DeleteActor(m_player);
        m_player = nullptr;
    }

    void World::DeleteEnemyShip()
    {
        DeleteActor(m_enemyShip);
        m_enemyShip = nullptr;
    }
}