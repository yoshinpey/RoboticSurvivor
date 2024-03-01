#pragma once

#include "InputManager.h"
#include "PlayerBase.h"

class Aim;
class StateManager;
class Text;

class Player : public PlayerBase
{
private:
    float nowHp_;               // HP 

    XMFLOAT3 velocity_;         // �ړ�����
    XMFLOAT3 movement_;         // �ړ���
    float acceleration_;        // �����x
    float friction_;            // ���C��(�����x)

    float jumpFriction_;        // �؋󒆂̌����x
    int gravity_;               // �d��
    float jumpDelta_;           // �K���Ȃ����������l
    bool jumping_;              // �W�����v�\�ȏ�Ԃ��ǂ���

    //int hGroundModel_;          // ���f���n���h��
    //bool useRayCast_;           // ���C�L���X�g���g�����ǂ���

    // �C���X�^���X
    StateManager* pStateManager_;       // ��Ԃ�؂�ւ���p
    Text* pText_;                        // �e�L�X�g�\���p
    Aim* pAim_;                         // �G�C���Ăяo���p

    PlayerParameter parameter_;     // �p�����[�^
    PlayerStatus status_;           // �X�e�[�^�X

public:
    Player(GameObject* parent);     // �R���X�g���N�^
    ~Player();                      // �f�X�g���N�^

    void Initialize() override;     // ������
    void Update() override;         // �X�V
    void Draw() override;           // �`��
    void Release() override;        // �J��

    // �A�N�V����
    void Walk();                    // ����
    void Run();                     // ����
    void ApplyMovement(const XMFLOAT3& moveVector, float speed);
    void ApplyDeceleration();       
    void Jump();                    // �W�����v
    void PlayerHitPoint();          // �̗�

    // �ړ��v�Z���s���֐�
    XMFLOAT3 CalculateMoveInput();

    // �d�͂�K�p����
    void ApplyGravity();

    //bool RayCastStage(XMFLOAT3 position);

    // �n�ʂɂ��Ă��邩�ǂ����𔻒肷��
    bool OnGround() const { return transform_.position_.y <= 0; }
};
