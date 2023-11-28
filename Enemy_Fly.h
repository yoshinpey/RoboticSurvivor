#pragma once
#include "Engine/GameObject.h"

//���V�G���Ǘ�����N���X
class Enemy_Fly : public GameObject
{
    int hModel_;    //���f���ԍ�
    const float JUMP_HEIGHT = 1.0f;     // �W�����v�̍���
    const float WALK_SPEED = 0.05f;     // ��������
    const float RUN_SPEED = 0.10f;      // ���鑬��
public:
    Enemy_Fly(GameObject* parent);  //�R���X�g���N�^
    ~Enemy_Fly();                   //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};