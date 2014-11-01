#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Actor.h"
#include "Drawing.h"

namespace asteroids
{
    enum PlayerState {
        MOVING_FORWARD,
        MOVING_BACKWARD,
        ROTATING_CW,
        ROTATING_CCW
    };

    class Player : public Actor
    {
        public:
            Player();
            ~Player();

            virtual void OnMoveForward() override;
            virtual void OnMoveBackward() override;
            virtual void OnRotateCW() override;
            virtual void OnRotateCCW() override;
            virtual void OnUpdate(const World &world) override;
            virtual void OnRender() override;

            void AddState(int bit);
            void ClearState(int bit);
            bool IsIdle();
            bool IsMoving() const;
            bool IsMovingForward() const;
            bool IsMovingBackward() const;
            bool IsRotatingCW() const;
            bool IsRotatingCCW() const;

        private:
            void InitializeGeometry();
            bool IsTooFast() const;
            void Rotate(float angle);
            bool TestBit(int mask, int bit) const;

            int m_state;
            float m_angle;
            Vector2 m_uprigth;
            Vector2 m_accel;
    };
}

#endif //__PLAYER_H_
