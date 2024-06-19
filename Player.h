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

    bool isEnemyHit_;
    XMFLOAT3 knockDirection_;

public:
    Player(GameObject* parent);     // �R���X�g���N�^
    ~Player();                      // �f�X�g���N�^

    void Initialize() override;     // ������
    void Update() override;         // �X�V
    void Draw() override;           // �`��
    void Release() override;        // �J��

    void Walk();                    // ����
    void Run();                     // ����
    void ApplyMovement(const XMFLOAT3& moveVector, float speed);    // �ړ��K��
    void ApplyDeceleration();       // �����K��
    void Jump();                    // �W�����v
    XMFLOAT3 CalculateMoveInput();  // �ړ��v�Z
    void ApplyGravity();            // �d�͂�K�p
    void OnCollision(GameObject* pTarget) override; // �����ɓ�������

    // �n�ʂɂ��Ă��邩�ǂ����𔻒�
    bool Jumping() const { return transform_.position_.y >= 0; }
};
