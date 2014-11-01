#include "Player.h"
#include "World.h"

#include <iostream>

namespace asteroids
{
    const float PLAYER_ROTATION_ANGLE = 3; // degrees
    const float PLAYER_MAX_SPEED = 8;
    const float PLAYER_KINETIC_FRICTION = 0.99;

    Player::Player()
    {
        InitializeGeometry();
        m_angle = 180;
        m_vel = Vector2(0, 0);
        m_accel = Vector2(0.05, 0.05);
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
            m_vel *= PLAYER_KINETIC_FRICTION;
        }
    }

    void Player::RotateCW()
    {
        Rotate(PLAYER_ROTATION_ANGLE);
    }

    void Player::RotateCCW()
    {
        Rotate(-PLAYER_ROTATION_ANGLE);
    }

    void Player::Rotate(float angle)
    {
        m_angle += angle;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);

        // Normalize Angle
        if(m_angle > 360)
            m_angle -= 360;
        if(m_angle <= 0)
            m_angle += 360;
    }

    void Player::MoveForward()
    {
        if(!IsTooFast())
        {
            m_vel.x += m_uprigth.x * m_accel.x;
            m_vel.y += m_uprigth.y * m_accel.y;
        }
    }

    void Player::MoveBackward()
    {
        if(!IsTooFast())
        {
            m_vel.x += m_uprigth.x * -m_accel.x;
            m_vel.y += m_uprigth.y * -m_accel.y;
        }
    }

    bool Player::IsTooFast() const
    {
        return fabs(m_vel.x) > PLAYER_MAX_SPEED
            || fabs(m_vel.y) > PLAYER_MAX_SPEED;
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