#pragma once
#include "Engine/GameObject.h"

//�n��G���Ǘ�����N���X
class Enemy_Ground : public GameObject
{
    int hModel_;    //���f���ԍ�

public:
    Enemy_Ground(GameObject* parent);//�R���X�g���N�^
    ~Enemy_Ground();                //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};