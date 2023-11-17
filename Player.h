#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

#include "InputManager.h"

//��l�����Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;                // ���f���ԍ�   
    int maxHp_, nowHp_;         // HP 

    const float JUMP_HEIGHT = 1.5f;     //�W�����v�̍���
    const float WALK_SPEED = 0.2f;      //��������
    const float RUN_SPEED = 0.3f;       //���鑬��

    float walkSpeed_;           // ���s���x
    float runSpeed_;            // ���s���x

    int gravity_;               // �d��
    float jumpVelocity_;        // �����x
    float jumpDelta_;           // �K���Ȃ����������l
    float flightTime_;          // �W�����v�o�ߎ���
    bool canJump_;              // �W�����v�\�ȏ�Ԃ��ǂ���

    // -----�t���O------------
    // �n�ʂɂ���
    bool onGround_ = transform_.position_.y <= 0;
    // �ړ����͂�����Ƃ��͐^
    bool isMoving_ = InputManager::IsMoveForward() || InputManager::IsMoveLeft() || InputManager::IsMoveBackward() || InputManager::IsMoveRight();
    //------------------------

    Text* pNum;                 //�e�L�X�g

public:
    Player(GameObject* parent);     //�R���X�g���N�^
    ~Player();                      //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
    
    //�A�N�V����
    void Move();                    //�v���C���[�̈ړ�
    void Jump();                    //�W�����v
    void PlayerHitPoint();          //�̗�

    //�v���C���[���W�̃Q�b�^�[
    XMFLOAT3 GetPlaPos() { return transform_.position_; }

};