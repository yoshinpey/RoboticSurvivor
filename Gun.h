
#pragma once
#include "Engine/GameObject.h"

//銃を管理するクラス
class Gun : public GameObject
{
    int hModel_;                    // モデル番号
    int shotCoolTime_;              // 一時的にクールタイムを保管しておく変数
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

    // 銃弾の速度と射出方向を計算する
    XMFLOAT3 CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed);

    // 銃弾を生成する
    template<class T>
    void ShootBullet();

};