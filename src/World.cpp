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
        Vector2 direction = m_player.GetUpRightVector();

        if(m_player.GetState() == PlayerState::MOVING_FORWARD)
        {
            m_player.SetVel(2 * direction);
        }
        else if(m_player.GetState() == PlayerState::MOVING_BACKWARD)
        {
            m_player.SetVel(2 * -direction);
        }

        m_player.Update(*this);
    }

    void World::OnKeyDown(unsigned char key)
    {
        switch(key)
        {
            case 'w':
                m_player.ChangeState(PlayerState::MOVING_FORWARD);
            break;
            case 's':
                m_player.ChangeState(PlayerState::MOVING_BACKWARD);
            break;
            case 'a':
                m_player.RotateCCW();
            break;
            case 'd':
                m_player.RotateCW();
            break;
        }
    }

    void World::OnKeyUp(unsigned char key)
    {

    }

    void World::OnMouseMove(int x, int y) {

    }

    void World::OnMouseClick(int button, int state, int x, int y) {

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