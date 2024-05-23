#pragma once
#include "Character.h"

// �}���`�ɑΉ�������Ӗ����o�邩���m��Ȃ����x�̖��Ӗ��N���X
class PlayerBase : public Character
{
    // �ړ��֘A�̍\����
    struct PlayerParameter
    {
        XMFLOAT3 velocity_{ 0.0f, 0.0f, 0.0f };      // �ړ�����
        XMFLOAT3 movement_{ 0.0f, 0.0f, 0.0f };      // �ړ���
        float acceleration_{ 0.03f };                // �����x
        float friction_{ 0.85f };                    // ���C��(�����x)
        float jumpFriction_{ 1.15f };                // �؋󒆂̌����x
        int gravity_{ -1 };                          // �d��
        float jumpDelta_{ 0.01f };                   // �K���Ȃ����������l
        bool jumping_{ false };                      // �W�����v���͐^�ɂȂ�t���O

        // �f�t�H���g�R���X�g���N�^
        PlayerParameter() = default;
    };

protected:
    PlayerParameter playerParams_;  // �ړ��֘A�̃p�����[�^

public:
    PlayerBase(GameObject* parent, std::string name)
        : Character(parent, name)
    {
    }

    virtual ~PlayerBase() = default;
};
