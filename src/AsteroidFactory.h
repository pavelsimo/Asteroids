#ifndef __ASTEROIDFACTORY_H_
#define __ASTEROIDFACTORY_H_

#include <vector>
#include "Asteroid.h"

namespace asteroids
{
    class AsteroidFactory
    {
        public:
            AsteroidFactory();
            ~AsteroidFactory();
            Asteroid* Create(AsteroidSize size, float speed = 2.f);
            Asteroid* CreateSmallAsteroid(float speed);
            Asteroid* CreateMediumAsteroid(float speed);
            Asteroid* CreateBigAsteroid(float speed);
    };
}


#endif //__ASTEROIDFACTORY_H_
