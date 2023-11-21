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
    const float WALK_SPEED = 0.1f;      //��������
    const float RUN_SPEED = 0.2f;       //���鑬��

    float walkSpeed_;           // ���s���x
    float runSpeed_;            // ���s���x
    XMFLOAT3 velocity_;         // �ړ�����
    XMFLOAT3 movement_;         // �ړ���
    float acceleration_;        // �����x
    float friction_;            // ���C��(�����x)
    float moveDelta_;           //  �K���Ȃ����������l

    int gravity_;               // �d��
    float jumpVelocity_;        // �����x
    float jumpDelta_;           // �K���Ȃ����������l
    bool canJump_;              // �W�����v�\�ȏ�Ԃ��ǂ���

    Text* pNum;                 //�e�L�X�g

    ////////// �t���O//////////
    bool isMoving_;             // �ړ����Ă��邩�ǂ���

    //////////////////////////

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