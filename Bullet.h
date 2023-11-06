#pragma once
#include "Engine/GameObject.h"

//�e�e���Ǘ�����N���X
class Bullet : public GameObject
{
    int hModel_;            //���f���ԍ�    
    int BulletKill_;        //�e�����Ԃŏ���
    XMFLOAT3 move_;         //�e�̓���

public:
    Bullet(GameObject* parent);     //�R���X�g���N�^
    ~Bullet();                      //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    //�e�̈ʒu�ݒ�p
    void SetMove(XMFLOAT3 move) { move_ = move; }
};