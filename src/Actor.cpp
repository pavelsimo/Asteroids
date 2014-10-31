#include "Actor.h"

namespace asteroids
{
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
        OnRender();
    }

    void Actor::Update(World const &world)
    {
        OnUpdate(world);
        // update AABB2
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