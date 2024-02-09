#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// 地上敵を管理するクラス
class Enemy_Explosion : public EnemyBase
{
    int hModel_;  // モデル番号
    SphereCollider* pCollision_;

    // 各ステータス
    float walkSpeed_;
    float attackPower_;
    float attackCooldown_;
    float detectPlayerDistance_;
    float patrolRadius_;
    float approachDistance_;
    float attackDistance_;

public:
    Enemy_Explosion(GameObject* parent);   // コンストラクタ
    ~Enemy_Explosion() override;           // デストラクタ
    void Initialize() override;         // 初期化
    void Update() override;             // 更新
    void Draw() override;               // 描画
    void Release() override;            // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget);


    void attack() override;
};
