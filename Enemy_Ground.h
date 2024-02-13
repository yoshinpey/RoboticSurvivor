#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// 地上敵を管理するクラス
class Enemy_Ground : public EnemyBase
{
    int hModel_;  // モデル番号
    SphereCollider* pCollision_;

    // 構造体のインスタンス
    EnemyStatus status_;
    EnemyAlgorithm algorithm_;

public:
    Enemy_Ground(GameObject* parent);   // コンストラクタ
    ~Enemy_Ground() override;           // デストラクタ
    void Initialize() override;         // 初期化
    void Update() override;             // 更新
    void Draw() override;               // 描画
    void Release() override;            // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget);

    void Attack() override;

    /*
    void loadStatsFromXML(const std::string& filename);
    void LoadWalkSpeedFromJson(const std::string& filename);
    */

};
