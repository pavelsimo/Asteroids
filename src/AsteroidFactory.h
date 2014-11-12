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
            Asteroid* Create(AsteroidSize size, int speed = 2);
            Asteroid* CreateSmallAsteroid(int speed);
            Asteroid* CreateMediumAsteroid(int speed);
            Asteroid* CreateBigAsteroid(int speed);
    };
}


#endif //__ASTEROIDFACTORY_H_
