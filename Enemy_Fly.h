#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

//���V�G���Ǘ�����N���X
class Enemy_Fly : public EnemyBase
{
    int hModel_;    //���f���ԍ�

    //CharacterBase characterStatus_;
    ///////////////////////////�萔///////////////////////////
    //const float JUMP_HEIGHT = 1.50f;    // �W�����v�̍���
    //const float WALK_SPEED = 0.07f;     // ��������
    //const float RUN_SPEED = 0.10f;      // ���鑬��

    //const float ATK = 1.0f;             // �U����
    //const float MAX_HP = 1.0f;          // �̗�
    //////////////////////////////////////////////////////////
public:
    Enemy_Fly(GameObject* parent);  // �R���X�g���N�^
    ~Enemy_Fly();                   // �f�X�g���N�^
    void Initialize() override;     // ������
    void Update() override;         // �X�V
    void Draw() override;           // �`��
    void Release() override;        // �J��
};