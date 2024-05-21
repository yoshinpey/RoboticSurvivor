#pragma once
#include "InputManager.h"
#include "PlayerBase.h"

class Aim;
class StateManager;
class Text;
class Gauge;

class Player : public PlayerBase
{
private:

private:
    // �C���X�^���X
    StateManager* pStateManager_;       // ��Ԃ�؂�ւ���p
    Text* pText_;                       // �e�L�X�g�\���p
    Aim* pAim_;                         // �G�C���Ăяo���p
    Gauge* pGauge_;                     // HP�Q�[�W

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
    void PlayerHitPoint();          // �̗�
    XMFLOAT3 CalculateMoveInput();  // �ړ��v�Z
    void ApplyGravity();            // �d�͂�K�p
    void OnCollision(GameObject* pTarget) override; // �����ɓ�������

    // �n�ʂɂ��Ă��邩�ǂ����𔻒�
    bool Jumping() const { return transform_.position_.y >= 0; }
};
