#include <iostream>
#include <algorithm>

#include "World.h"

namespace asteroids
{
    World::World(const float width, const float height)
    {
        m_width = width;
        m_height = height;
        m_player.SetPosition(Vector2(width / 2, height / 2));
        srand(time(NULL));
        CreateAsteroids(AsteroidSize::BIG, 5);
        CreateAsteroids(AsteroidSize::MEDIUM, 2);
        CreateAsteroids(AsteroidSize::SMALL, 2);
    }

    World::~World()
    {
        // Clean bullets
        for(auto it = m_bullets.begin(); it != m_bullets.end(); it++)
        {
            delete *it;
        }
        m_bullets.clear();

        // Clean asteroids
        for(auto it = m_asteroids.begin(); it != m_asteroids.end(); it++)
        {
            delete *it;
        }
        m_asteroids.clear();
    }

    void World::Render()
    {
        m_player.Render();
        RenderAsteroids();
        RenderBullets();
    }

    void World::Update()
    {
        m_player.Update(*this);
        UpdateAsteroids();
        UpdateBullets();
        CleanBullets();
        ResolveBulletsCollisions();
        ResolvePlayerCollisions();
    }

    void World::OnKeyDown(unsigned char key)
    {
        switch(key)
        {
            case 'w':
            case 'W':
                m_player.AddState(PlayerState::MOVING_FORWARD);
            break;
            case 's':
            case 'S':
                m_player.AddState(PlayerState::MOVING_BACKWARD);
            break;
            case 'a':
            case 'A':
                m_player.AddState(PlayerState::ROTATING_CCW);
            break;
            case 'd':
            case 'D':
                m_player.AddState(PlayerState::ROTATING_CW);
            break;
            case ' ':
                m_player.AddState(PlayerState::SHOOTING);
            break;
        }
    }

    void World::OnKeyUp(unsigned char key)
    {
        switch(key)
        {
            case 'w':
            case 'W':
                m_player.ClearState(PlayerState::MOVING_FORWARD);
                break;
            case 's':
            case 'S':
                m_player.ClearState(PlayerState::MOVING_BACKWARD);
                break;
            case 'a':
            case 'A':
                m_player.ClearState(PlayerState::ROTATING_CCW);
                break;
            case 'd':
            case 'D':
                m_player.ClearState(PlayerState::ROTATING_CW);
                break;
            case ' ':
                m_player.ClearState(PlayerState::SHOOTING);
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

    void World::CleanBullets()
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
                    Asteroid* mediumAsteroid = m_asteroidFactory.CreateMediumAsteroid();
                    mediumAsteroid->SetPosition(asteroid.GetPosition());
                    m_asteroids.push_back(mediumAsteroid);
                }
            break;
            case AsteroidSize::MEDIUM:
                for(int i = 0; i < numAsteroids; ++i)
                {
                    Asteroid* smallAsteroid = m_asteroidFactory.CreateSmallAsteroid();
                    smallAsteroid->SetPosition(asteroid.GetPosition());
                    m_asteroids.push_back(smallAsteroid);
                }
            break;
        }
    }

    void World::ResolvePlayerCollisions()
    {
        for(auto i = m_asteroids.begin(); i != m_asteroids.end(); i++)
        {
            Asteroid* asteroid = *i;
            if(m_player.IsColliding(*asteroid))
            {
                CreatePlayerDebris();
                break;
            }
        }
    }

    void World::ResolveBulletsCollisions()
    {
        // Bullets and asteroids collisions
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

    void World::CreateAsteroids(AsteroidSize size, int numAsteroids)
    {
        float w = m_width;
        float h = m_height;
        float x[] = {0, w, 0, w};
        float y[] = {0, 0, h, h};
        for(int i = 0, j = 0; i < numAsteroids; ++i, ++j)
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
        // TODO: (Pavel) Implement RespawnPlayer()
    }
}