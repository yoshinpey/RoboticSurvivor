#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

class Player;

// 地上敵を管理するクラス
class Enemy_Explosion : public EnemyBase
{
    int hModel_;                            // モデル番号
    Player* pPlayer_;
    float currentHp_;               // 現在のHP 

public:
    Enemy_Explosion(GameObject* parent);   // コンストラクタ
    ~Enemy_Explosion() override;           // デストラクタ
    void Initialize() override;             // 初期化
    void Update() override;                 // 更新
    void Draw() override;                   // 描画
    void Release() override;                // 開放

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
