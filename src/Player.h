#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Actor.h"
#include "Drawing.h"

namespace asteroids
{
    enum PlayerState {
        IDLE,
        MOVING_FORWARD,
        MOVING_BACKWARD,
    };

    class Player : public Actor
    {
        public:
            Player();
            ~Player();

            void MoveForward();
            void MoveBackward();
            void RotateCW();
            void RotateCCW();
            virtual void OnUpdate(const World &world) override;
            virtual void OnRender() override;

            void ChangeState(PlayerState state);
            PlayerState GetState();
            Vector2 GetUpRightVector() const;

        private:
            void InitializeGeometry();
            PlayerState m_state;
            float m_angle;
            Vector2 m_uprigth;
    };
}

#endif //__PLAYER_H_
