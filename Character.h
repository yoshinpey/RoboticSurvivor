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
        float knockBackStrength_; // �m�b�N�o�b�N�̋���

        CommonParameter();
    };

    // �X�e�[�^�X
    struct CommonStatus
    {
        float maxHp_;         // �̗�
        float currentHp_;     // ���݂̗̑�

        CommonStatus();
    };

    CommonParameter commonParameter_;
    CommonStatus commonStatus_;

public:
    Character(GameObject* parent, std::string name);
    virtual ~Character();

    // HP�𑝂₷
    void IncreaseHp(float amount);

    // HP�����炷
    void DecreaseHp(float amount);

    // �n�ʂɂ��Ă��邩�ǂ����𔻒�
    bool Jumping() const { return transform_.position_.y >= 0; }
};
