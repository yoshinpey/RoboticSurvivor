#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// 地上敵を管理するクラス
class Enemy_Ground : public EnemyBase
{
    int hModel_;                        // モデル番号
    SphereCollider* pCollision_;        // コリジョン
    float lastAngle_;
public:
    Enemy_Ground(GameObject* parent);   // コンストラクタ
    ~Enemy_Ground() override;           // デストラクタ
    void Initialize() override;         // 初期化
    void Update() override;             // 更新

    // 内積計算
    float CalculateDotProduct(const XMFLOAT3& directionToPlayer);

    // 移動速度に応じた移動量でプレイヤーに接近する
    void ApproachPlayer(const XMFLOAT3& directionToPlayer);

    // 敵の体をプレイヤーの方向へ回転させる
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer);

    void Draw() override;               // 描画
    void Release() override;            // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget);

    void Attack() override;

};
