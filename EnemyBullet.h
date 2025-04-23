#pragma once
#include "Engine/GameObject.h"

// 銃弾の基底クラス
class EnemyBullet : public GameObject
{
private:
    float damage_;          // ダメージ
    float speed_;           // スピード
    int killTimer_;         // 消失時間
    float collisionScale_;  // 当たり判定のサイズ

protected:
    XMFLOAT3 moveDirection_;        // 移動の速度と方向
    SphereCollider* pCollision_;    // 当たり判定

public:
    EnemyBullet(GameObject* parent, std::string name)
        :GameObject(parent, name), moveDirection_(0, 0, 0), pCollision_(nullptr)
    {
    };
    virtual ~EnemyBullet() = default;

    // 銃弾の移動を設定
    void SetMoveDirection(const XMFLOAT3& direction) { moveDirection_ = direction; }
};