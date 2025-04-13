#pragma once
#include "EnemyBase.h"

class Player;

// 爆破敵を管理するクラス
class Enemy_Explosion : public EnemyBase
{
    int hModel_;                    // モデル番号
    int explodeTimeLimit_;          // 爆発までの時間制限
    float explodeTimer_;            // 現在の爆発タイマー
    bool isInExplosionRange_;       // 爆発範囲内にいるかどうか
    float explodeScale_;            // 爆発半径
    XMFLOAT3 directionToPlayer_;    // プレイヤーへの方向
    float distanceToPlayer_;        // プレイヤーとの距離

public:
    Enemy_Explosion(GameObject* parent);    // コンストラクタ
    ~Enemy_Explosion() override;            // デストラクタ
    void Initialize() override;             // 初期化
    void Update() override;                 // 更新
    void Draw() override;                   // 描画
    void Release() override;                // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget);

    // 攻撃
    void Attack() override;

    // 爆発までの時間制限をセット
    void SetExplodeTimer(int explodeTimeLimit) { explodeTimeLimit_ = explodeTimeLimit; };
};
