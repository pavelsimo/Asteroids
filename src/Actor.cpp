#include <iostream>
#include "Actor.h"
#include "World.h"

namespace asteroids
{
    Actor::Actor()
    : m_position(0, 0),
      m_vel(0, 0),
      m_direction(0, 0)
    {

    }

    Actor::~Actor()
    {

    }

    void Actor::Render()
    {
        OnRender();
    }

    void Actor::OnRender()
    {
        // default behavior
    }

    void Actor::Update(World& world)
    {
        OnUpdate(world);

        // update boundaries
        float angle = m_direction.CalcYawDegrees();
        m_aabb2.Empty();
        for(auto it = m_points.begin(); it != m_points.end(); it++)
        {
            Vector2 p = *it;
            p.RotateDegrees(angle);
            p += m_position;
            m_aabb2.Add(p);
        }

        // wrap actor
        if(m_aabb2.max.x < world.GetLeft())
            m_position.x = world.GetRight() - m_aabb2.GetWidth();
        if(m_aabb2.max.y < world.GetTop())
            m_position.y = world.GetBottom() - m_aabb2.GetHeight();
        if(m_aabb2.min.x > world.GetRight())
            m_position.x = world.GetLeft();
        if(m_aabb2.min.y > world.GetBottom())
            m_position.y = world.GetTop();
    }

    void Actor::OnUpdate(World& world)
    {
        // default behavior
    }

    void Actor::MoveForward()
    {
        OnMoveForward();
    }

    void Actor::OnMoveForward()
    {
        // default behavior
    }

    void Actor::MoveBackward()
    {
        OnMoveBackward();
    }

    void Actor::OnMoveBackward()
    {
        // default behavior
    }

    void Actor::RotateCW()
    {
        OnRotateCW();
    }

    void Actor::OnRotateCW()
    {
        // default behavior
    }

    void Actor::RotateCCW()
    {
        OnRotateCCW();
    }

    void Actor::OnRotateCCW()
    {
        // default behavior
    }

    bool Actor::IsColliding(const Actor &actor)
    {
        AABB2 lhs = GetAABB2();
        AABB2 rhs = actor.GetAABB2();
        return lhs.Intersects(rhs);
    }

    void Actor::SetPosition(const Vector2 &position)
    {
        m_position = position;
    }

    void Actor::SetVel(const Vector2 &vel) 
    {
        m_vel = vel;
    }

    void Actor::SetDirection(const Vector2 &direction)
    {
        m_direction = direction;
    }

    void Actor::SetPoints(const PointList &points)
    {
        m_points = points;
    }

    Vector2 Actor::GetVel() const
    {
        return m_vel;
    }

    Vector2 Actor::GetPosition() const
    {
        return m_position;
    }

    Vector2 Actor::GetDirection() const
    {
        return m_direction;
    }

    AABB2 Actor::GetAABB2() const
    {
        return m_aabb2;
    }

    const PointList &Actor::GetPoints() const
    {
        return m_points;
    }
}