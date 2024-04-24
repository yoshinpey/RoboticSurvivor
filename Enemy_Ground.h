#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

class Player;

// 地上敵を管理するクラス
class Enemy_Ground : public EnemyBase
{
    int hModel_;                        // モデル番号
    float currentHp_;               // 現在のHP 
    bool isFirstHit_;               // 初回ヒットフラグ
    XMFLOAT3 firstPosition_;        // 銃弾ヒット位置保存用

public:
    Enemy_Ground(GameObject* parent);   // コンストラクタ
    ~Enemy_Ground() override;           // デストラクタ
    void Initialize() override;         // 初期化
    void Update() override;             // 更新
    void Draw() override;               // 描画
    void Release() override;            // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget);

    // 攻撃
    void Attack() override;

    // HPを取得
    float GetCurrentHp() const override { return currentHp_; }

    // HPを増やす
    void IncreaseHp(float amount) override;

    // HPを減らす
    void DecreaseHp(float amount) override;

    // 死亡判定
    bool IsDead() const override { return currentHp_ <= 0; }
};
