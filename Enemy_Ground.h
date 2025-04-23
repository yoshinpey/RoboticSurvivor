#pragma once
#include "EnemyBase.h"

class Player;

// 地上敵を管理するクラス
class Enemy_Ground : public EnemyBase
{
    int hModel_;                        // モデル番号
    XMFLOAT3 directionToPlayer_;        // プレイヤーへの方向
    float distanceToPlayer_;            // プレイヤーとの距離
    XMFLOAT3 targetDirectionToPlayer_{ 0,0,1 }; // プレイヤーの方向（更新された最新）
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

};
