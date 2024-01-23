#include "CharacterBase.h"

CharacterBase::CharacterBase(GameObject* parent)
    :GameObject(parent, "CharacterBase"), maxHp_(0), attackPower_(0), jumpVelocity_(0.0f), walkSpeed_(0.0f), runSpeed_(0.0f)
{
}

CharacterBase::~CharacterBase()
{
}

// �L�����N�^�[�̃X�e�[�^�X���Z�b�g
void CharacterBase::SetCharacterStatus(int maxHp, int attackPower)
{
    maxHp_ = maxHp;
    attackPower_ = attackPower;
}

// �ړ��֘A�̃p�����[�^���Z�b�g
void CharacterBase::SetMovementParameters(float jumpVelocity, float walkSpeed, float runSpeed)
{
    jumpVelocity_ = jumpVelocity;
    walkSpeed_ = walkSpeed;
    runSpeed_ = runSpeed;
}