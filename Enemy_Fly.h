#pragma once
#include "Engine/Model.h"
#include "EnemyBase.h"

//浮遊敵を管理するクラス
class Enemy_Fly : public EnemyBase
{
    int hModel_;                        // モデル番号
    SphereCollider* pCollision_;        // コリジョン
    //SphereCollider* pHeadCollision_;        // コリジョン

public:
    Enemy_Fly(GameObject* parent);      // コンストラクタ
    ~Enemy_Fly();                       // デストラクタ
    void Initialize() override;         // 初期化
    void Update() override;             // 更新
    void Draw() override;               // 描画
    void Release() override;            // 開放

    // 何かに当たった
    void OnCollision(GameObject* pTarget) override;

    //void HeadOnCollision(GameObject* pTarget) override;

    void Attack() override;

   
};