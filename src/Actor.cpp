#include <iostream>
#include "Actor.h"
#include "Drawing.h"
#include "World.h"

namespace asteroids
{
    // TODO: (Pavel) Create a ZeroVector constant
    Actor::Actor()
    : m_position(Vector2(0, 0)),
      m_vel(Vector2(0, 0)),
      m_direction(Vector2(0, 0))
    {

    }

    Actor::~Actor()
    {

    }

    void Actor::Render()
    {
        // TODO: (Pavel) Drawing should be here
        OnRender();
    }

    void Actor::Update(World const &world)
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

        /*
        std::cout << "AABB2: (" << m_aabb2.min.x << "," << m_aabb2.min.y << ") ("
                << m_aabb2.max.x << "," << m_aabb2.max.y << ") " << std::endl;
        */

        // wrap actor
        if(m_aabb2.max.x < world.GetLeft()) m_position.x = world.GetRight() - m_aabb2.GetWidth();
        if(m_aabb2.max.y < world.GetTop()) m_position.y = world.GetBottom() - m_aabb2.GetHeight();
        if(m_aabb2.min.x > world.GetRight()) m_position.x = world.GetLeft();
        if(m_aabb2.min.y > world.GetBottom()) m_position.y = world.GetTop();
    }

    void Actor::OnRender()
    {

    }

    void Actor::OnUpdate(World const &world)
    {

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

    void Actor::SetVel(const Vector2 &vel) {
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