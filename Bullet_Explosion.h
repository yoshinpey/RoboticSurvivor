#pragma once
#include "BulletBase.h"
#include <unordered_set>

class BulletBase;

// 銃弾を管理するクラス
class Bullet_Explosion : public BulletBase
{
    int hModel_;
    float verticalSpeed_;   // 垂直方向のスピード変数

    // ヒットした敵のデータを入れておく
    std::unordered_set<GameObject*> hitEnemies;

public:
    Bullet_Explosion(GameObject* parent);
    ~Bullet_Explosion();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget);

    // 弾の向きを対象方向へ回転させる
    void RotateToTarget(XMFLOAT3& directionToPlayer);

};