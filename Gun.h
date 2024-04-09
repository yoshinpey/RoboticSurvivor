
#pragma once
#include "Engine/GameObject.h"

//�e���Ǘ�����N���X
class Gun : public GameObject
{
    int hModel_;                    // ���f���ԍ�
    int shotCoolTime_;              // �ꎞ�I�ɃN�[���^�C����ۊǂ��Ă����ϐ�
    int normalShotCool_;            // 
    int explosionShotCool_;         // 
    int hSound_;

public:
    Gun(GameObject* parent);
    ~Gun();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // �e�e�̑��x�Ǝˏo�������v�Z����
    XMFLOAT3 CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed);

    // �e�e�𐶐�����
    template<class T>
    void ShootBullet();

};