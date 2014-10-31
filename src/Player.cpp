#include "Player.h"
#include "World.h"

#include <iostream>

namespace asteroids
{
    const float PLAYER_SPEED = 2;
    const float DRAG = 0.2;
    const float ROTATION_ANGLE = 20;

    Player::Player()
    {
        InitializeGeometry();
        m_angle = 180;
        m_vel = Vector2(0, 0);
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);
        m_state = PlayerState::IDLE;
    }

    Player::~Player()
    {

    }

    void Player::OnUpdate(const World &world)
    {
        m_position += m_vel;
    }

    void Player::RotateCW()
    {
        m_angle += ROTATION_ANGLE;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);

        std::cout << m_angle << " "  << m_direction.x << " " << m_direction.y << " " << std::endl;
    }

    void Player::RotateCCW()
    {
        m_angle -= ROTATION_ANGLE;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);

        std::cout << m_angle << " "  << m_direction.x << " " << m_direction.y << " " << std::endl;
    }

    void Player::OnRender()
    {
        DrawPolygon(m_points, m_position.x, m_position.y, m_angle);
    }

    void Player::InitializeGeometry()
    {
        // Initialize ship geometry
        m_points.push_back(Vector2(0.0f, 20.0f));
        m_points.push_back(Vector2(12.0f, -10.0f));
        m_points.push_back(Vector2(6.0f, -4.0f));
        m_points.push_back(Vector2(-6.0f, -4.0f));
        m_points.push_back(Vector2(-12.0f, -10.0f));
    }

    Vector2 Player::GetUpRightVector() const {
        return m_uprigth;
    }

    void Player::ChangeState(PlayerState state)
    {
        m_state = state;
    }

    PlayerState Player::GetState()
    {
        return m_state;
    }
}