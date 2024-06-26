#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"
#include <unordered_set>

class Player;

//浮遊敵を管理するクラス
class Enemy_Fly : public EnemyBase
{
    int hModel_;                        // モデル番号
    XMFLOAT3 currentPosition_;          // 現在地

    // ヒットした敵のデータを入れておく
    std::unordered_set<GameObject*> hitEnemies;

public:
    Enemy_Fly(GameObject* parent);      // コンストラクタ
    ~Enemy_Fly();                       // デストラクタ
    void Initialize() override;         // 初期化
    void Update() override;             // 更新
    void Draw() override;               // 描画
    void Release() override;            // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget);

    // 攻撃
    void Attack() override;

};