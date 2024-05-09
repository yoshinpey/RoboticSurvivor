
#pragma once
#include "Engine/GameObject.h"
#include <vector>

struct BulletInfo
{
    int ct;
};

enum class BulletType;

//銃を管理するクラス
class Gun : public GameObject
{
    int hModel_;                    // モデル番号
    int hSound_;                    // サウンド
    XMFLOAT3 moveDirection_;        

    std::vector<BulletInfo> bulletInfoList_;

public:
    Gun(GameObject* parent);
    ~Gun();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // 銃弾の速度と射出方向を計算する
    XMFLOAT3 CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed);

    // 銃弾を生成する
    template<class T>
    void ShootBullet(BulletType type);

    XMFLOAT3 GetMoveDirection() const { return moveDirection_; }
};
