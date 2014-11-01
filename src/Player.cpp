#include "Player.h"
#include "World.h"

#include <iostream>

namespace asteroids
{
    const float PLAYER_SPEED = 2;
    const float ACCELERATION_FORWARD = 0.1;
    const float ACCELERATION_BACKWARD = -0.1;
    const float FRICTION_COEFFICIENT = 0.98;
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
        if(m_state == PlayerState::MOVING_FORWARD || m_state == PlayerState::MOVING_BACKWARD)
        {
            m_position += m_vel;
        }
        m_vel = FRICTION_COEFFICIENT * m_vel;
    }

    void Player::RotateCW()
    {
        // TODO: (Pavel) Make this two functions share a common method
        m_angle += ROTATION_ANGLE;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);

        if(m_angle > 360)
            m_angle -= 360;
        if(m_angle < -360)
            m_angle += 360;

        std::cout << m_angle << " "  << m_direction.x << " " << m_direction.y << " " << std::endl;
    }

    void Player::RotateCCW()
    {
        m_angle -= ROTATION_ANGLE;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_uprigth.SetUnitLengthAndYawDegrees(m_angle + 90);

        if(m_angle > 360)
            m_angle -= 360;
        if(m_angle < -360)
            m_angle += 360;

        std::cout << m_angle << " "  << m_direction.x << " " << m_direction.y << " " << std::endl;
    }


    void Player::MoveForward()
    {
        m_vel.x += m_uprigth.x * ACCELERATION_FORWARD;
        m_vel.y += m_uprigth.y * ACCELERATION_FORWARD;
    }

    void Player::MoveBackward()
    {
        m_vel.x += m_uprigth.x * ACCELERATION_BACKWARD;
        m_vel.y += m_uprigth.y * ACCELERATION_BACKWARD;
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