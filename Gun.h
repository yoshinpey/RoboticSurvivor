#pragma once
#include "Engine/GameObject.h"
//Player�̎q��
//�e���Ǘ�����N���X
class Gun : public GameObject
{
    int hModel_;    //���f���ԍ�
    float Bullet_speed;

public:
    Gun(GameObject* parent);        //�R���X�g���N�^
    ~Gun();                         //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
};