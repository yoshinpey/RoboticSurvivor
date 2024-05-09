
#pragma once
#include "Engine/GameObject.h"
#include <vector>

struct BulletInfo
{
    int ct;
};

enum class BulletType;

//�e���Ǘ�����N���X
class Gun : public GameObject
{
    int hModel_;                    // ���f���ԍ�
    int hSound_;                    // �T�E���h
    XMFLOAT3 moveDirection_;        

    std::vector<BulletInfo> bulletInfoList_;

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
    void ShootBullet(BulletType type);

    XMFLOAT3 GetMoveDirection() const { return moveDirection_; }
};
