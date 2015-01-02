#include "Asteroid.h"
#include "World.h"

namespace asteroids
{
    const float ASTEROID_ROTATION_ANGLE = 1.f;

    Asteroid::Asteroid(float radius, int numVertices, float speed)
    : Actor(),
      m_radius(radius),
      m_numVertices(numVertices),
      m_speed(speed)
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
            p.SetUnitLengthAndYawDegrees(static_cast<float>(angle));
            int halfRadius = static_cast<int>(m_radius * 0.5f);
            float displacement = static_cast<float>(m_radius - Random<int>(1, halfRadius));
            p *= displacement;
            m_points.push_back(p);
        }

        // Initialize the velocity
        int positiveX = Random<int>(0, 1);
        int positiveY = Random<int>(0, 1);
        Vector2 dir = Vector2(
            static_cast<float>(Random<int>(1, 100)), 
            static_cast<float>(Random<int>(1, 100))
        );
        if(!positiveX) dir.x = -dir.x;
        if(!positiveY) dir.y = -dir.y;
        dir.Normalize();
        m_vel = dir * m_speed;
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