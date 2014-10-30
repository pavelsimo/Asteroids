#include "World.h"

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