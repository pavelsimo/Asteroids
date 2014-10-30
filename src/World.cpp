#include "World.h"
#include "Vector2.h"

#include <vector>

namespace asteroids {

    World::World()
    {

    }

    World::World(const float width, const float height)
    : m_width(width),
      m_height(height)
    {

    }

    World::~World()
    {

    }

    void World::Render()
    {
        // TEST

        std::vector<Vector2> points;

        points.push_back(Vector2(m_width/2.0 + 0.0f, m_height/2.0 + 20.0f));
        points.push_back(Vector2(m_width/2.0 + 12.0f, m_height/2.0 + -10.0f));
        points.push_back(Vector2(m_width/2.0 + 6.0f, m_height/2.0 + -4.0f));
        points.push_back(Vector2(m_width/2.0 + -6.0f, m_height/2.0 + -4.0f));
        points.push_back(Vector2(m_width/2.0 + -12.0f, m_height/2.0 + -10.0f));

        DrawPolygon(points);
    }

    void World::Update()
    {

    }

    void World::OnKeyDown(unsigned char key)
    {

    }

    void World::OnKeyUp(unsigned char key)
    {

    }

    void World::OnMouseMove(int x, int y) {

    }

    void World::OnMouseClick(int button, int state, int x, int y) {

    }

    float World::GetWidth() const
    {
        return m_width;
    }

    float World::GetHeight() const
    {
        return m_height;
    }

    float World::GetLeft() const
    {
        return 0;
    }

    float World::GetRight() const
    {
        return m_width;
    }

    float World::GetBottom() const
    {
        return m_height;
    }

    float World::GetTop() const
    {
        return 0;
    }
}