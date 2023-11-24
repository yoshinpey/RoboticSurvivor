#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
    : gravity_(-9.8f), acceleration_(0.01f), friction_(0.8f)
{
}

PhysicsEngine::~PhysicsEngine() 
{
}

void PhysicsEngine::ApplyGravity(XMFLOAT3& velocity, float delta)
{
    // d—Í‚Å—‰º
    velocity.y += gravity_ * delta;
}

void PhysicsEngine::ApplyJump(XMFLOAT3& velocity, float jumpVelocity, float delta, bool& canJump, float& yPosition, float groundLevel)
{
    // ‘Ø‹ó’†
    if (!canJump)
    {
        // d—Í‚Å—‰º
        ApplyGravity(velocity, delta);

        // ’…’n‚µ‚½‚Æ‚«
        if (yPosition <= groundLevel)
        {
            yPosition = groundLevel;
            velocity.y = 0.0f;
            canJump = true;
        }
    }
}

void PhysicsEngine::ApplyFriction(XMFLOAT3& velocity, float delta)
{
    velocity.x *= pow(friction_, delta);
    velocity.z *= pow(friction_, delta);
}

void PhysicsEngine::ApplyMovement(XMFLOAT3& position, const XMFLOAT3& movement)
{
    position.x += movement.x;
    position.y += movement.y;
    position.z += movement.z;
}