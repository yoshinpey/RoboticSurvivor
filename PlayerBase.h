#pragma once
#include "Engine/GameObject.h"

// �v���C���[�̌��ɂȂ�N���X
class PlayerBase : public GameObject
{
protected:
    // �ړ��֘A�̃p�����[�^
    struct PlayerParameter
    {
        float jumpVelocity_ = 0.2f;    // �W�����v��
        float walkSpeed_ = 0.1f;    // ���s���x
        float runSpeed_ = 0.2f;     // ���s���x
    };

    // �X�e�[�^�X
    struct PlayerStatus
    {
        float maxHp_ = 100;         // �̗�
    };

public:
    PlayerBase(GameObject* parent, std::string name)
        :GameObject(parent, name)
    {
    }

    virtual ~PlayerBase() 
    {
    };
};