#pragma once
#include "Engine/GameObject.h"

//���V�G���Ǘ�����N���X
class Enemy_Fly : public GameObject
{
    int hModel_;    //���f���ԍ�

public:
    Enemy_Fly(GameObject* parent);  //�R���X�g���N�^
    ~Enemy_Fly();                   //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};