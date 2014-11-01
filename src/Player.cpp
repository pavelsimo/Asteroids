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
        m_state = 0;
    }

    Player::~Player()
    {

    }

    void Player::OnUpdate(const World &world)
    {
        if(IsMovingForward()) MoveForward();
        if(IsMovingBackward()) MoveBackward();
        if(IsRotatingCCW()) RotateCCW();
        if(IsRotatingCW()) RotateCW();

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
        return IsMovingForward() || IsMovingBackward();
    }

    void Player::OnMoveForward() {
        if(!IsTooFast())
        {
            m_vel.x += m_uprigth.x * m_accel.x;
            m_vel.y += m_uprigth.y * m_accel.y;
        }
    }

    void Player::OnMoveBackward() {
        if(!IsTooFast())
        {
            m_vel.x += m_uprigth.x * -m_accel.x;
            m_vel.y += m_uprigth.y * -m_accel.y;
        }
    }

    void Player::OnRotateCW() {
        Rotate(PLAYER_ROTATION_ANGLE);
    }

    void Player::OnRotateCCW() {
        Rotate(-PLAYER_ROTATION_ANGLE);
    }

    void Player::AddState(int bit)
    {
        m_state |= (1 << bit);
    }

    void Player::ClearState(int bit)
    {
        m_state &= ~(1 << bit);
    }

    bool Player::IsIdle()
    {
        return m_state == 0;
    }

    bool Player::IsMovingForward() const
    {
        return TestBit(m_state, PlayerState::MOVING_FORWARD);
    }

    bool Player::IsMovingBackward() const
    {
        return TestBit(m_state, PlayerState::MOVING_BACKWARD);
    }

    bool Player::IsRotatingCW() const
    {
        return TestBit(m_state, PlayerState::ROTATING_CW);
    }

    bool Player::IsRotatingCCW() const
    {
        return TestBit(m_state, PlayerState::ROTATING_CCW);
    }

    bool Player::TestBit(int mask, int bit) const
    {
        return (mask & (1 << bit)) != 0;
    }
}