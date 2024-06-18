#include "Character.h"
#include <cmath>

// �R���X�g���N�^
Character::Character(GameObject* parent, std::string name)
    : GameObject(parent, name)
{
}

// �f�X�g���N�^
Character::~Character() = default;

// CommonParameter�̃R���X�g���N�^
Character::CommonParameter::CommonParameter()
    : jumpVelocity_(0.2f), walkSpeed_(0.1f), runSpeed_(0.2f), knockBackStrength_(10.0f)
{
}

// CommonStatus�̃R���X�g���N�^
Character::CommonStatus::CommonStatus()
    : maxHp_(100.0f), currentHp_(maxHp_)
{
}

// HP�𑝂₷
void Character::IncreaseHp(float amount)
{
    commonStatus_.currentHp_ += amount;
    if (commonStatus_.currentHp_ > commonStatus_.maxHp_) {
        commonStatus_.currentHp_ = commonStatus_.maxHp_;
    }
}

// HP�����炷
void Character::DecreaseHp(float amount)
{
    commonStatus_.currentHp_ -= amount;
    if (commonStatus_.currentHp_ <= 0) {
        commonStatus_.currentHp_ = 0;
        if (IsCharacterDead()) KillMe();
    }
}

// ���S����
bool Character::IsCharacterDead()
{
    return commonStatus_.currentHp_ <= 0.0f;
}

// �m�b�N�o�b�N����
void Character::KnockBack(const XMFLOAT3& direction, float strength)
{
    // �m�b�N�o�b�N�x�N�g�����v�Z
    XMFLOAT3 knockBackVector = { direction.x * strength, direction.y * strength, direction.z * strength };

    // �m�b�N�o�b�N�x�N�g�����L�����N�^�[�̃|�W�V�����ɉ��Z
    transform_.position_.x += knockBackVector.x;
    transform_.position_.y += knockBackVector.y;
    transform_.position_.z += knockBackVector.z;
}