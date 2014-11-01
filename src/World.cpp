#include "World.h"

#include <iostream>

namespace asteroids {

    World::World(const float width, const float height)
    : m_width(width),
      m_height(height)
    {
        m_player.SetPosition(Vector2(width / 2, height / 2));
    }

    World::~World()
    {

    }

    void World::Render()
    {
        m_player.Render();
    }

    void World::Update()
    {
        m_player.Update(*this);
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
}