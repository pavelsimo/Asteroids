#include "AsteroidFactory.h"

namespace asteroids
{

    AsteroidFactory::AsteroidFactory()
    {

    }

    AsteroidFactory::~AsteroidFactory()
    {

    }

    Asteroid *AsteroidFactory::Create(AsteroidSize size, int speed)
    {
        switch(size)
        {
            case AsteroidSize::SMALL:
                return CreateSmallAsteroid(speed);
            case AsteroidSize::MEDIUM:
                return CreateMediumAsteroid(speed);
            case AsteroidSize::BIG:
                return CreateBigAsteroid(speed);
        }
        return nullptr;
    }

    Asteroid *AsteroidFactory::CreateSmallAsteroid(int speed)
    {
        float radius = 15.0f;
        int numVertices = 15;
        Asteroid* asteroid = new Asteroid(radius, numVertices, speed);
        asteroid->SetSize(AsteroidSize::SMALL);
        return asteroid;
    }

    Asteroid *AsteroidFactory::CreateMediumAsteroid(int speed)
    {
        float radius = 30.0f;
        int numVertices = 15;
        Asteroid* asteroid = new Asteroid(radius, numVertices, speed);
        asteroid->SetSize(AsteroidSize::MEDIUM);
        return asteroid;
    }

    Asteroid *AsteroidFactory::CreateBigAsteroid(int speed)
    {
        float radius = 60.0f;
        int numVertices = 15;
        Asteroid* asteroid = new Asteroid(radius, numVertices, speed);
        asteroid->SetSize(AsteroidSize::BIG);
        return asteroid;
    }
}