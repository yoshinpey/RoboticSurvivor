#include "CharacterBase.h"

CharacterBase::CharacterBase()
    : maxHp_(0), jumpVelocity_(0.0f), walkSpeed_(0.0f), runSpeed_(0.0f), attackPower_(0)
{
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::SetStatus(int maxHp, float jumpVelocity, float walkSpeed, float runSpeed)
{
    maxHp_ = maxHp;
    jumpVelocity_ = jumpVelocity;
    walkSpeed_ = walkSpeed;
    runSpeed_ = runSpeed;
}

void CharacterBase::SetAttackPower(int attackPower)
{
    attackPower_ = attackPower;
}
