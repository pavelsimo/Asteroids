#include "Player.h"
#include "World.h"

#include <iostream>


namespace asteroids
{
    const float PLAYER_ROTATION_ANGLE = 3.0f; // degrees
    const float PLAYER_MAX_SPEED = 6.f;
    const float PLAYER_SHOOT_TIMEOUT = 20;
    const float PLAYER_DRAG = 0.999;

    Player::Player()
    {
        InitializeGeometry();
        Initialize();
    }

    Player::~Player()
    {

    }

    void Player::Initialize()
    {
        m_angle = 180;
        m_vel = Vector2(0, 0);
        m_accel = Vector2(0.04, 0.04);
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_upright.SetUnitLengthAndYawDegrees(m_angle + 90);
        m_state = 0;
        m_shootTimeout = 0;
    }

    void Player::OnUpdate(World &world)
    {
        if(IsShooting() && !m_shootTimeout) Shoot(world);
        if(IsMovingForward()) MoveForward();
        if(IsMovingBackward()) MoveBackward();
        if(IsRotatingCCW()) RotateCCW();
        if(IsRotatingCW()) RotateCW();

        // Moving the ship
        m_position += m_vel;
        m_vel *= PLAYER_DRAG;

        // Decreasing the shoot timeout
        m_shootTimeout = std::max(0, m_shootTimeout - 1);
    }

    void Player::Rotate(float angle)
    {
        m_angle += angle;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
        m_upright.SetUnitLengthAndYawDegrees(m_angle + 90);
        NormalizeAngle();
    }

    void Player::Shoot(World &world)
    {
        Bullet *bullet = new Bullet();

        // Set bullet position
        Vector2 bulletPos = m_position;
        bulletPos.x += m_upright.x * 16.0f;
        bulletPos.y += m_upright.y * 16.0f;
        bullet->SetPosition(bulletPos);

        // Set bullet velocity
        Vector2 bulletVelocity = m_upright;
        bulletVelocity.x *= (2 * PLAYER_MAX_SPEED);
        bulletVelocity.y *= (2 * PLAYER_MAX_SPEED);
        bullet->SetVel(bulletVelocity);

        // Adding the bullet to the world list
        world.AddBullet(bullet);

        // Adding some time before allow shooting again
        m_shootTimeout = PLAYER_SHOOT_TIMEOUT;
    }

    bool Player::IsTooFast() const
    {
        return fabs(m_vel.x) > PLAYER_MAX_SPEED
            || fabs(m_vel.y) > PLAYER_MAX_SPEED;
    }

    void Player::OnRender()
    {
        // Render the player
        DrawPolygon(m_points, m_position.x, m_position.y, m_angle);
    }

    void Player::InitializeGeometry()
    {
        m_points.push_back(Vector2(0.0f, 20.0f));
        m_points.push_back(Vector2(12.0f, -10.0f));
        m_points.push_back(Vector2(6.0f, -4.0f));
        m_points.push_back(Vector2(-6.0f, -4.0f));
        m_points.push_back(Vector2(-12.0f, -10.0f));
    }

    void Player::OnMoveForward() {
        NormalizeVelocity();
        ApplyImpulse(m_upright, m_accel);
    }

    void Player::OnMoveBackward() {
        NormalizeVelocity();
        ApplyImpulse(m_upright, -m_accel);
    }

    void Player::ApplyImpulse(const Vector2 &dir, const Vector2 &accel)
    {
        m_vel.x += dir.x * accel.x;
        m_vel.y += dir.y * accel.y;
    }

    void Player::NormalizeVelocity()
    {
        if(IsTooFast())
        {
            float speed = m_vel.CalcLength();
            m_vel.x = (m_vel.x / speed) * PLAYER_MAX_SPEED;
            m_vel.y = (m_vel.y / speed) * PLAYER_MAX_SPEED;
        }
    }

    void Player::NormalizeAngle()
    {
        if(m_angle > 360) m_angle -= 360;
        if(m_angle <= 0) m_angle += 360;
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

    void Player::RemoveState(int bit)
    {
        m_state &= ~(1 << bit);
    }

    bool Player::TestBit(int mask, int bit) const
    {
        return (mask & (1 << bit)) != 0;
    }

    bool Player::IsIdle()
    {
        return m_state == 0;
    }

    bool Player::IsMoving() const {
        return IsMovingForward() || IsMovingBackward();
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

    bool Player::IsShooting() const {
        return TestBit(m_state, PlayerState::SHOOTING);
    }

    bool Player::IsRotatingCCW() const
    {
        return TestBit(m_state, PlayerState::ROTATING_CCW);
    }
}