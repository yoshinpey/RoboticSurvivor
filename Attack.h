#pragma once
#include "Engine/GameObject.h"

//�ߐڍU�����Ǘ�����N���X
class Attack : public GameObject
{
    int hModel_;    //���f���ԍ�

public:
    Attack(GameObject* parent);//�R���X�g���N�^
    ~Attack();//�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};