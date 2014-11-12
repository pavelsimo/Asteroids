#include "Asteroid.h"
#include "World.h"

namespace asteroids
{
    const float ASTEROID_ROTATION_ANGLE = 1.f;

    Asteroid::Asteroid(float radius, int numVertices)
    : Actor(),
      m_radius(radius),
      m_numVertices(numVertices)
    {
        Initialize();
    }

    Asteroid::~Asteroid()
    {

    }

    void Asteroid::Initialize()
    {
        // Initialize the geometry
        int steps = 360 / m_numVertices;
        for(int angle = 0; angle < 360; angle+=steps)
        {
            Vector2 p;
            p.SetUnitLengthAndYawDegrees(angle);
            p *= (m_radius - Random<int>(1, m_radius * 0.5f));
            m_points.push_back(p);
        }

        // Initialize the velocity
        int positiveX = Random<int>(0, 1);
        int positiveY = Random<int>(0, 1);
        Vector2 vel = Vector2(Random<int>(1, 100), Random<int>(1, 100));
        float speed = Random<int>(10, 20) / 20.0f;
        if(!positiveX) vel.x = -vel.x;
        if(!positiveY) vel.y = -vel.y;
        vel.Normalize();
        m_vel = vel * speed;
    }

    void Asteroid::OnUpdate(World &world)
    {
        m_position += m_vel;
        m_angle += ASTEROID_ROTATION_ANGLE;
        m_direction.SetUnitLengthAndYawDegrees(m_angle);
    }

    void Asteroid::OnRender()
    {
        DrawPolygon(m_points, m_position.x, m_position.y, m_angle, 2);
    }

    AsteroidSize Asteroid::GetSize() const
    {
        return m_size;
    }

    void Asteroid::SetSize(AsteroidSize size)
    {
        m_size = size;
    }
}