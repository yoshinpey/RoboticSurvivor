#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CharacterBase.h"

class Player : public GameObject
{
private:
    int hModel_;                // ���f���ԍ�   
    int maxHp_, nowHp_;         // HP 

    CharacterBase characterStatus_; //�L�����N�^�[�����p�����[�^
    ///////////////////////////�萔///////////////////////////
    const float JUMP_HEIGHT = 1.50f;    // �W�����v�̍���
    const float WALK_SPEED = 0.2f;     // ��������
    const float RUN_SPEED = 0.30f;      // ���鑬��

    const float ATK = 0.0f;             // �U����
    const float MAX_HP = 1.0f;          // �̗�
    //////////////////////////////////////////////////////////

    StateManager* stateManager_;     // ��Ԃ�؂�ւ���p

    float walkSpeed_;           // ���s���x
    float runSpeed_;            // ���s���x
    XMFLOAT3 velocity_;         // �ړ�����
    XMFLOAT3 movement_;         // �ړ���
    float acceleration_;        // �����x
    float friction_;            // ���C��(�����x)

    int gravity_;               // �d��
    float jumpVelocity_;        // �W�����v�̏����x
    float jumpDelta_;           // �K���Ȃ����������l
    bool canJump_;              // �W�����v�\�ȏ�Ԃ��ǂ���

    Text* pNum;                 // �e�L�X�g

    // �t���O
    bool isMoving_;             // �ړ����Ă��邩�ǂ���

public:
    //�f�o�b�N�p
    bool testDRW = false;
    Player(GameObject* parent);     // �R���X�g���N�^
    ~Player();                      // �f�X�g���N�^

    void Initialize() override;     // ������
    void Update() override;         // �X�V
    void Draw() override;           // �`��
    void Release() override;        // �J��

    // �A�N�V����
    void Move();                    // �v���C���[�̈ړ�
    void Walk();                    // ����
    void Run();                     // ����
    void ApplyMovement(const XMFLOAT3& moveVector, float speed);
    void ApplyDeceleration();
    void Jump();                    // �W�����v
    void PlayerHitPoint();          // �̗�

    // �v���C���[���W�̃Q�b�^�[
    XMFLOAT3 GetPlaPos() const { return transform_.position_; }

    // �ړ��v�Z���s���֐�
    XMFLOAT3 CalculateMoveInput();
};
