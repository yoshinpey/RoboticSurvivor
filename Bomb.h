#pragma once
#include "Engine/GameObject.h"

//���e���Ǘ�����N���X
class Bomb : public GameObject
{
    int hModel_;    //���f���ԍ�

public:
    Bomb(GameObject* parent);       //�R���X�g���N�^
    ~Bomb();                        //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};