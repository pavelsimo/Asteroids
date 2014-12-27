#include "AsteroidGame.h"
#include "LOpenAL.h"

const int SCREEN_WIDTH = 1136;
const int SCREEN_HEIGHT = 640;
const std::string SCREEN_TITLE = "Asteroid";

int main(int argc, char** argv)
{
    alutInit (&argc, argv);

    std::shared_ptr<asteroids::AsteroidGame> game(new asteroids::AsteroidGame(SCREEN_TITLE,
            SCREEN_WIDTH, SCREEN_HEIGHT));
    game->Run();

    alutExit();

    return 0;
}