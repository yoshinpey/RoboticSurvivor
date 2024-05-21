#pragma once
#include "Engine/GameObject.h"

class Character : public GameObject
{
protected:
    // �ړ��֘A�̃p�����[�^
    struct CommonParameter
    {
        float jumpVelocity_;     // �W�����v��
        float walkSpeed_;        // ���s���x
        float runSpeed_;         // ���s���x

        CommonParameter()
            : jumpVelocity_(0.2f), walkSpeed_(0.1f), runSpeed_(0.2f)
        {
        }
    };

    // �X�e�[�^�X
    struct CommonStatus
    {
        float maxHp_;         // �̗�
        float currentHp_;     // ���݂̗̑�
        CommonStatus()
            : maxHp_(100.0f), currentHp_(maxHp_)
        {
        }
    };

    CommonParameter commonParameter_;
    CommonStatus commonStatus_;

public:
    Character(GameObject* parent, std::string name)
        : GameObject(parent, name)
    {
    }

    virtual ~Character()
    {
    };

    // HP�𑝂₷
    void IncreaseHp(float amount)
    {
        commonStatus_.currentHp_ += amount;
        if (commonStatus_.currentHp_ > commonStatus_.maxHp_) {
            commonStatus_.currentHp_ = commonStatus_.maxHp_;
        }
    }

    // HP�����炷
    void DecreaseHp(float amount)
    {
        commonStatus_.currentHp_ -= amount;
        if (commonStatus_.currentHp_ < 0) {
            commonStatus_.currentHp_ = 0;
        }
    }
    float GetCurrentHp() const { return commonStatus_.currentHp_; }
    float GetMaxHp() const { return commonStatus_.maxHp_; }
};
