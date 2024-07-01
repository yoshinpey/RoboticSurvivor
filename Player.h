#pragma once
#include "InputManager.h"
#include "Character.h"

class Aim;
class StateManager;
class Text;
class Gauge;

class Player : public Character
{
private:

    // �v���C���[�ŗL�̃p�����[�^
    struct PlayerParameter
    {
        XMFLOAT3 velocity_{ 0.0f, 0.0f, 0.0f };      // �ړ����x
        XMFLOAT3 movement_{ 0.0f, 0.0f, 0.0f };      // �ړ���
        float acceleration_{ 0.03f };                // �����x
        float friction_{ 0.85f };                    // ���C��(�����x)
        float jumpFriction_{ 1.15f };                // �؋󒆂̌����x
        int gravity_{ -1 };                          // �d��
        float jumpDelta_{ 0.01f };                   // �W�����v�̍���
        bool jumping_{ false };                      // �W�����v���t���O

        PlayerParameter() = default;
    };

    // �C���X�^���X
    PlayerParameter playerParams_;      // �v���C���[�ŗL�̃p�����[�^
    StateManager* pStateManager_;       // ��Ԃ�؂�ւ���p
    Aim* pAim_;                         // �G�C���Ăяo���p
    Gauge* pGauge_;                     // HP�Q�[�W

    bool isEnemyHit_;                   // �G�l�~�[�ɓ��������Ƃ��^(���G���Ԑݒ�p)
    XMFLOAT3 knockDirection_;           // �m�b�N�o�b�N����

public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // ����
    void Walk();

    // ����
    void Run();

    // �ړ��K��
    void ApplyMovement(const XMFLOAT3& moveVector, float maxSpeed);

    // �����K��
    void ApplyDeceleration();

    // �W�����v
    void Jump();

    // �ړ��v�Z
    XMFLOAT3 CalculateMoveInput();

    // �d�͂�K�p
    void ApplyGravity();

    // �����ɓ�������
    void OnCollision(GameObject* pTarget) override;

    // �m�b�N�o�b�N�K���֐�
    void ApplyKnockback();

    // ���G�����ǂ���
    bool IsInvincible() const { return isEnemyHit_; }
};
