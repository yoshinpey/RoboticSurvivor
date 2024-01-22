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
    Enemy_Ground(GameObject* parent, const XMFLOAT3& spawnPosition);

    // デストラクタ
    ~Enemy_Ground();

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

    // 開放
    void Release() override;

    // GetNameの実装
    std::string GetName() const
    {
        // ここに名前を取得する処理を追加
        return "GroundEnemy";
    }

    // GetIdの実装
    int GetId() const
    {
        // ここにIDを取得する処理を追加
        return 1;
    }
};