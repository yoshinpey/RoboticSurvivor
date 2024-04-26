#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"
#include <unordered_set>

class Player;

// 地上敵を管理するクラス
class Enemy_Explosion : public EnemyBase
{
    int hModel_;                    // モデル番号

    // ヒットした敵のデータを入れておく
    std::unordered_set<GameObject*> hitEnemies;

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

};
