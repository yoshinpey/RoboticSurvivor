#pragma once
#include "Engine/GameObject.h"

//���ڕW(�N���X�^��)���Ǘ�����N���X
class Crystal : public GameObject
{
    int hModel_;    //���f���ԍ�

public:
    Crystal(GameObject* parent);    //�R���X�g���N�^
    ~Crystal();                     //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};