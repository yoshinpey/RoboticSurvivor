#pragma once
#include "BulletBase.h"
#include <unordered_set>

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

    // ヒットした敵のデータを入れておく
    std::unordered_set<GameObject*> hitEnemies;

public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void RotateToTarget(XMFLOAT3& directionToPlayer);

    void OnCollision(GameObject* pTarget);
};