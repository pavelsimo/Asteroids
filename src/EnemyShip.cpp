#include "EnemyShip.h"
#include "MathUtilities.h"
#include "World.h"
#include <iostream>

namespace asteroids
{
    const int ENEMYSHIP_SHOOT_TIMEOUT = 200;
    const int ENEMYSHIP_BULLET_SPEED = 3;
    const int ENEMYSHIP_BULLET_LIFESPAN = 100;
    const int ENEMYSHIP_RADIUS = 40;

    EnemyShip::EnemyShip()
    {
        InitializeGeometry();
    }

    EnemyShip::~EnemyShip()
    {

    }

    void EnemyShip::OnUpdate(World &world)
    {
        if(!m_shootTimeout)
        {
            Shoot(world);
        }

        float amplitude = 2.5f;
        m_position.x += Random<int>(5, 10) / 10.f;
        Vector2 dir;
        dir.SetUnitLengthAndYawDegrees(m_position.x);
        m_position.y += amplitude * dir.y;
        m_shootTimeout = std::max(0, m_shootTimeout - 1);
    }

    void EnemyShip::OnRender()
    {
        // TODO: (Pavel) Move this to Drawing
        glPushMatrix();
        glTranslatef(m_position.x , m_position.y, 0);
        glRotatef(180, 1, 0, 0);

        //Ships outer body
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.0f,0.0f);
            glVertex2f(9.0f,5.0f);
            glVertex2f(12.0f,9.0f);
            glVertex2f(18.0f,9.0f);
            glVertex2f(21.0f,5.0f);
            glVertex2f(30.0f,0.0f);
            glVertex2f(22.0f,-5.0f);
            glVertex2f(8.0f,-5.0f);
        glEnd();

        //middle line on ship
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.0f,0.0f);
            glVertex2f(30.0f,0.0f);
        glEnd();

        // upper line on ship
        glBegin(GL_LINE_LOOP);
            glVertex2f( 9.0f,5.0f);
            glVertex2f( 21.0f,5.0f);
        glEnd();

        // retro vertex points
        glPointSize(2);
        glBegin(GL_POINTS);
            glVertex2f(0.0f,0.0f);
            glVertex2f(9.0f,5.0f);
            glVertex2f(12.0f,9.0f);
            glVertex2f(18.0f,9.0f);
            glVertex2f(21.0f,5.0f);
            glVertex2f(30.0f,0.0f);
            glVertex2f(22.0f,-5.0f);
            glVertex2f(8.0f,-5.0f);
            glEnd();
        glPopMatrix();
    }

    void EnemyShip::InitializeGeometry()
    {
        // Using just the outer body for collisions
        m_points.push_back(Vector2(0.0f, 0.0f));
        m_points.push_back(Vector2(9.0f, 5.0f));
        m_points.push_back(Vector2(12.0f, 9.0f));
        m_points.push_back(Vector2(18.0f, 9.0f));
        m_points.push_back(Vector2(21.0f, 5.0f));
        m_points.push_back(Vector2(30.0f, 0.0f));
        m_points.push_back(Vector2(22.0f, -5.0f));
        m_points.push_back(Vector2(8.0f, -5.0f));
    }

    void EnemyShip::Shoot(World &world)
    {
        Bullet *bullet = new Bullet(ENEMYSHIP_BULLET_LIFESPAN);
        Vector2 playerPosition = world.GetPlayer().GetPosition();
        Vector2 bulletDirection = playerPosition - m_position;
        bulletDirection.Normalize();

        // Set bullet position
        Vector2 bulletPos = m_position;
        bulletPos.x += bulletDirection.x * ENEMYSHIP_RADIUS;
        bulletPos.y += bulletDirection.y * ENEMYSHIP_RADIUS;
        bullet->SetPosition(bulletPos);

        // Set bullet velocity
        Vector2 bulletVelocity = bulletDirection;
        bulletVelocity.x *= ENEMYSHIP_BULLET_SPEED;
        bulletVelocity.y *= ENEMYSHIP_BULLET_SPEED;
        bullet->SetVel(bulletVelocity);

        // Adding the bullet to the world list
        world.AddBullet(bullet);

        // Play fire sound
        world.GetSoundManager().Play(world.SOUND_FIRE, true);

        // Adding some time before allow shooting again
        m_shootTimeout = ENEMYSHIP_SHOOT_TIMEOUT;
    }
}


