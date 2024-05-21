#pragma once
#include "Character.h"

// �}���`�ɑΉ�������Ӗ����o�邩���m��Ȃ����x�̖��Ӗ��N���X
class PlayerBase : public Character
{
    // �ړ��֘A�̍\����
    struct MovementParameters 
    {
        XMFLOAT3 velocity{ 0.0f, 0.0f, 0.0f };      // �ړ�����
        XMFLOAT3 movement{ 0.0f, 0.0f, 0.0f };      // �ړ���
        float acceleration{ 0.03f };                // �����x
        float friction{ 0.85f };                    // ���C��(�����x)
        float jumpFriction{ 1.15f };                // �؋󒆂̌����x
        int gravity{ -1 };                          // �d��
        float jumpDelta{ 0.01f };                   // �K���Ȃ����������l
        bool jumping{ false };                      // �W�����v�\�ȏ�Ԃ��ǂ���

        // �f�t�H���g�R���X�g���N�^
        MovementParameters() = default;
    };

protected:
    MovementParameters movementParams_;  // �ړ��֘A�̃p�����[�^

public:
    PlayerBase(GameObject* parent, std::string name)
        : Character(parent, name)
    {
    }

    virtual ~PlayerBase() = default;
};
