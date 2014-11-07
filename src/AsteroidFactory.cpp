#include "AsteroidFactory.h"

namespace asteroids
{

    AsteroidFactory::AsteroidFactory()
    {

    }

    AsteroidFactory::~AsteroidFactory()
    {

    }

    Asteroid *AsteroidFactory::CreateSmallAsteroid()
    {
        float radius = 15.0f;
        int numVertices = 15;
        Asteroid* asteroid = new Asteroid(radius, numVertices);
        asteroid->SetSize(AsteroidSize::SMALL);
        return asteroid;
    }

    Asteroid *AsteroidFactory::CreateMediumAsteroid()
    {
        float radius = 30.0f;
        int numVertices = 15;
        Asteroid* asteroid = new Asteroid(radius, numVertices);
        asteroid->SetSize(AsteroidSize::MEDIUM);
        return asteroid;
    }

    Asteroid *AsteroidFactory::CreateBigAsteroid()
    {
        float radius = 60.0f;
        int numVertices = 15;
        Asteroid* asteroid = new Asteroid(radius, numVertices);
        asteroid->SetSize(AsteroidSize::BIG);
        return asteroid;
    }
}