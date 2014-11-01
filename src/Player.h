#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Actor.h"
#include "Drawing.h"

namespace asteroids
{
    enum PlayerState {
        IDLE,
        ROTATING_CW,
        ROTATING_CCW,
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

        private:
            void InitializeGeometry();
            bool IsMoving() const;

            PlayerState m_state;
            float m_angle;
            Vector2 m_uprigth;
            Vector2 m_accel;
    };
}

#endif //__PLAYER_H_
