#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

// 地上敵を管理するクラス
class Enemy_Ground : public EnemyBase
{
private:
    int hModel_;  // モデル番号
public:
    // コンストラクタ
    Enemy_Ground(GameObject* parent);

    // デストラクタ
    ~Enemy_Ground() override;

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

    // 開放
    void Release() override;
};
