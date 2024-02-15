#pragma once
#include "Engine/Text.h"

#include "InputManager.h"
#include "StateManager.h"
#include "PlayerCharacterBase.h"

class Aim;

class Player : public PlayerCharacterBase
{
private:
    int maxHp_, nowHp_;                 // HP 
    ///////////////////////////�萔///////////////////////////
    const float JUMP_HEIGHT = 0.2f;     // �W�����v�̍���
    const float WALK_SPEED = 0.1f;      // ��������
    const float RUN_SPEED = 0.2f;       // ���鑬��

    const float ATK = 0.0f;             // �U����
    const float MAX_HP = 1.0f;          // �̗�
    //////////////////////////////////////////////////////////

    float walkSpeed_;           // ���s���x
    float runSpeed_;            // ���s���x
    XMFLOAT3 velocity_;         // �ړ�����
    XMFLOAT3 movement_;         // �ړ���
    float acceleration_;        // �����x
    float friction_;            // ���C��(�����x)
    float jumpFriction_;        // ���C��(�����x)

    int gravity_;               // �d��
    float jumpVelocity_;        // �W�����v�̏����x
    float jumpDelta_;           // �K���Ȃ����������l
    bool canJump_;              // �W�����v�\�ȏ�Ԃ��ǂ���
    bool jumping_;              // �W�����v�\�ȏ�Ԃ��ǂ���
    int hGroundModel_;
    bool useRayCast_;

    // �C���X�^���X
    StateManager* stateManager_;        // ��Ԃ�؂�ւ���p    
    PlayerCharacterBase* pPlayerCharacterBase_;    // �L�����N�^�[�����p�����[�^
    Text* pNum;                         // �e�L�X�g
    Aim* pAim_;                         // �G�C��

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

    // �v���C���[���W�̃Q�b�^�[
    XMFLOAT3 GetPosition() const { return transform_.position_; }

    // �ړ��v�Z���s���֐�
    XMFLOAT3 CalculateMoveInput();

    // �d�͂�K�p����
    void ApplyGravity();

    bool RayCastStage(XMFLOAT3 position);

    // �n�ʂɂ��Ă��邩�ǂ����𔻒肷��
    bool OnGround() const { return transform_.position_.y <= 0; }
};
