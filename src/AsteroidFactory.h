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
            Asteroid* CreateSmallAsteroid();
            Asteroid* CreateMediumAsteroid();
            Asteroid* CreateBigAsteroid();
    };
}


#endif //__ASTEROIDFACTORY_H_
