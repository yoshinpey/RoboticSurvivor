#pragma once
#include "Engine/GameObject.h"

//�e���Ǘ�����N���X
class Gun : public GameObject
{
    int hModel_;    //���f���ԍ�
    float bulletSpeed_;
    float AttackCool_;
    float Cool_;
public:
    Gun(GameObject* parent);        //�R���X�g���N�^
    ~Gun();                         //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    // �e�e�̑��x�Ǝˏo�������v�Z����
    XMFLOAT3 CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed);

    // �e�e�𐶐�����
    template<class T>
    void ShootBullet();
};