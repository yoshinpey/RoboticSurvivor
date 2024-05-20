#pragma once
#include "Engine/GameObject.h"

class Character : public GameObject
{
protected:
    // �ړ��֘A�̃p�����[�^
    struct CharacterParameter
    {
        float jumpVelocity_ = 0.2f;     // �W�����v��
        float walkSpeed_ = 0.1f;        // ���s���x
        float runSpeed_ = 0.2f;         // ���s���x
    };

    // �X�e�[�^�X
    struct CharacterStatus
    {
        float maxHp_ = 100;         // �̗�
        float currentHp_ = 100;     // ���݂̗̑�
    };

    CharacterParameter parameter_;
    CharacterStatus status_;

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
        status_.currentHp_ += amount;
        if (status_.currentHp_ > status_.maxHp_) {
            status_.currentHp_ = status_.maxHp_;
        }
    }

    // HP�����炷
    void DecreaseHp(float amount)
    {
        status_.currentHp_ -= amount;
        if (status_.currentHp_ < 0) {
            status_.currentHp_ = 0;
        }
    }

    // �����ɓ�������
    virtual void OnCollision(GameObject* pTarget) = 0;

    float GetCurrentHp() const { return status_.currentHp_; }
    float GetMaxHp() const { return status_.maxHp_; }
};
