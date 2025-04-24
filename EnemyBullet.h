#pragma once
#include "Engine/GameObject.h"
#include <unordered_set>

// 銃弾の基底クラス
class EnemyBullet : public GameObject
{
private:
    float damage_;          // ダメージ
    float speed_;           // スピード
    int killTimer_;         // 消失時間
    float collisionScale_;  // 当たり判定のサイズ

    // ヒットした敵のデータを入れておく
    std::unordered_set<GameObject*> hitEnemies;

protected:
    XMFLOAT3 moveDirection_;        // 移動の速度と方向
    SphereCollider* pCollision_;    // 当たり判定

public:
    EnemyBullet(GameObject* parent, std::string name);
    virtual ~EnemyBullet() = default;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget);

    // 銃弾の移動を設定
    void SetMoveDirection(const XMFLOAT3& direction) { moveDirection_ = direction; }

    // 弾丸の速度を設定
    void SetDamage(const float& damage) { damage_ = damage; }
};