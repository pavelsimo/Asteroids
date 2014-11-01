#include "Player.h"
#include "World.h"

#include <iostream>

namespace asteroids
{
    const float ROTATION_ANGLE = 5;
    const float FRICTION = 0.99;

    Player::Player()
    {
        InitializeGeometry();
        m_angle = 180;
        m_vel = Vector2(0, 0);
        m_accel = Vector2(0.5, 0.5);
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);
        m_state = PlayerState::IDLE;
    }

    Player::~Player()
    {

    }

    void Player::OnUpdate(const World &world)
    {
        if(IsMoving())
        {
            m_position += m_vel;
        }
        else
        {
            m_position += m_vel;
            m_vel *= FRICTION;
        }
    }

    void Player::RotateCW()
    {
        // TODO: (Pavel) Make RotateCW() and RotateCCW() share a common method
        // TODO: (Pavel) Normalize Angles
        m_angle += ROTATION_ANGLE;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);
        //std::cout << m_angle << " "  << m_direction.x << " " << m_direction.y << " " << std::endl;
    }

    void Player::RotateCCW()
    {
        // TODO: (Pavel) Make RotateCW() and RotateCCW() share a common method
        // TODO: (Pavel) Normalize Angles
        m_angle -= ROTATION_ANGLE;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);
        //std::cout << m_angle << " "  << m_direction.x << " " << m_direction.y << " " << std::endl;
    }

    void Player::MoveForward()
    {
        m_vel.x += m_uprigth.x * m_accel.x;
        m_vel.y += m_uprigth.y * m_accel.y;
    }

    void Player::MoveBackward()
    {
        m_vel.x += m_uprigth.x * -m_accel.x;
        m_vel.y += m_uprigth.y * -m_accel.y;
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

    bool Player::IsMoving() const {
        return m_state == PlayerState::MOVING_FORWARD
            || m_state == PlayerState::MOVING_BACKWARD;
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