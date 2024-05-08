#pragma once
#include "BulletBase.h"

class BulletBase;
class Gun;

// 銃弾を管理するクラス
class Bullet_Explosion : public BulletBase
{
    int hModel_; 
    Gun* pGun_;

    bool isFirstHit_;    // 初めて当たった時

    float gravity_;         // 銃弾にかける重力
    float verticalSpeed_;   // スピード

public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void RotateToTarget(const XMFLOAT3& directionToPlayer);

    void OnCollision(GameObject* pTarget);
};