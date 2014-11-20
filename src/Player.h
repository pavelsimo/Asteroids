#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <vector>

#include "Drawing.h"
#include "Actor.h"
#include "Bullet.h"

namespace asteroids
{
    enum PlayerState
    {
        MOVING_FORWARD,
        MOVING_BACKWARD,
        ROTATING_CW,
        ROTATING_CCW,
        SHOOTING
    };

    class Player : public Actor
    {
        public:
            Player();
            ~Player();

            void Initialize();
            virtual void OnMoveForward() override;
            virtual void OnMoveBackward() override;
            virtual void OnRotateCW() override;
            virtual void OnRotateCCW() override;
            virtual void OnUpdate(World &world) override;
            virtual void OnRender() override;
            bool IsIdle();
            bool IsMoving() const;
            bool IsMovingForward() const;
            bool IsMovingBackward() const;
            bool IsRotatingCW() const;
            bool IsRotatingCCW() const;
            bool IsShooting() const;
            bool IsDead() const;
            void AddState(int bit);
            void RemoveState(int bit);
            void AddScore(unsigned int score);
            void SetScore(unsigned int score);
            unsigned int GetScore() const;
            void DecreaseOneLife();
            void SetLifes(unsigned int lifes);
            int GetLifes() const;

        private:
            void Shoot(World &world);
            void ApplyImpulse(const Vector2 &dir, const Vector2 &accel);
            void InitializeGeometry();
            void NormalizeVelocity();
            void NormalizeAngle();
            bool IsTooFast() const;
            void Rotate(float angle);
            bool TestBit(int mask, int bit) const;

            unsigned int m_score;
            int m_lifes;
            int m_state;
            float m_angle;
            Vector2 m_upright;
            Vector2 m_accel;
            int m_shootTimeout;
    };
}

#endif //__PLAYER_H_
