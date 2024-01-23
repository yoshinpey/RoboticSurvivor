#include "CharacterBase.h"

CharacterBase::CharacterBase(GameObject* parent)
    :GameObject(parent, "CharacterBase"), maxHp_(0), attackPower_(0), jumpVelocity_(0.0f), walkSpeed_(0.0f), runSpeed_(0.0f)
{
}

CharacterBase::~CharacterBase()
{
}

// キャラクターのステータスをセット
void CharacterBase::SetCharacterStatus(int maxHp, int attackPower)
{
    maxHp_ = maxHp;
    attackPower_ = attackPower;
}

// 移動関連のパラメータをセット
void CharacterBase::SetMovementParameters(float jumpVelocity, float walkSpeed, float runSpeed)
{
    jumpVelocity_ = jumpVelocity;
    walkSpeed_ = walkSpeed;
    runSpeed_ = runSpeed;
}