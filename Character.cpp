#include "Character.h"
#include <cmath>

// �R���X�g���N�^
Character::Character(GameObject* parent, std::string name)
    : GameObject(parent, name), knockDirection_(0.0f, 0.0f, 0.0f), isKnockBackActive_(false)
{
}

// �f�X�g���N�^
Character::~Character() = default;

// CommonParameter�̃R���X�g���N�^
Character::CommonParameter::CommonParameter()
    : jumpVelocity_(0.2f), walkSpeed_(0.1f), runSpeed_(0.2f), knockBackStrength_(1.0f)
{
}

// CommonStatus�̃R���X�g���N�^
Character::CommonStatus::CommonStatus()
    : maxHp_(100.0f), currentHp_(maxHp_)
{
}

// �X�V���\�b�h
void Character::Update()
{
    if (isKnockBackActive_)
    {
        // �m�b�N�o�b�N����
        knockDirection_.x -= knockDirection_.x * commonParameter_.knockBackStrength_;
        knockDirection_.z -= knockDirection_.z * commonParameter_.knockBackStrength_;

        // Y���̃m�b�N�o�b�N�����Əd�͓K�p
        knockDirection_.y -= knockDirection_.y * (commonParameter_.knockBackStrength_ * 3.0f);

        transform_.position_.x += knockDirection_.x;
        transform_.position_.y += knockDirection_.y;
        transform_.position_.z += knockDirection_.z;

        // �n�ʂɓ��B������W�����v��Ԃ����Z�b�g
        if (transform_.position_.y < 0)
        {
            transform_.position_.y = 0;
            knockDirection_.y = 0; // Y�����̃m�b�N�o�b�N�����Z�b�g
        }

        // �m�b�N�o�b�N���قƂ�ǂȂ��Ȃ�����t���O�����Z�b�g
        if (fabs(knockDirection_.x) < 0.01f && fabs(knockDirection_.z) < 0.01f && fabs(knockDirection_.y) < 0.01f)
        {
            isKnockBackActive_ = false;
        }
    }
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
    // �m�b�N�o�b�N������ݒ�
    knockDirection_ = direction;
    knockDirection_.x *= strength;
    knockDirection_.y = 1.0f; // ������ւ̃m�b�N�o�b�N�͌Œ�l
    knockDirection_.z *= strength;

    isKnockBackActive_ = true;
}
