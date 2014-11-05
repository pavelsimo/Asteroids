#include "Bullet.h"

namespace asteroids
{
    const int BULLET_RADIUS = 3;
    const int BULLET_VERTEX = 8;
    const int BULLET_LINE_WIDTH = 1;
    const int BULLET_LIFE_SPAN = 60;

    Bullet::Bullet()
    : m_lifeSpan(BULLET_LIFE_SPAN)
    {
        InitializeGeometry();
    }

    Bullet::~Bullet()
    {

    }

    bool Bullet::CanDelete() const {
        return !m_lifeSpan;
    }

    void Bullet::InitializeGeometry()
    {
        int steps = 360 / BULLET_VERTEX;
        for(int angle = 0; angle < 360; angle+=steps)
        {
            Vector2 p;
            p.SetUnitLengthAndYawDegrees(angle);
            p *= BULLET_RADIUS;
            m_points.push_back(p);
        }
    }

    void Bullet::OnUpdate(const World &world)
    {
        m_position += m_vel;
        m_lifeSpan = std::max(0, m_lifeSpan - 1);
    }

    void Bullet::OnRender()
    {
        DrawPolygon(m_points, m_position.x, m_position.y, 0, BULLET_LINE_WIDTH);
    }
}