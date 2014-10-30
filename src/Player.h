#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Actor.h"

class Player : public Actor
{
    public:
        Player();
        ~Player();

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
};

#endif //__PLAYER_H_
