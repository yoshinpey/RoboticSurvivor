#pragma once
#include "EnemyBase.h"

class Player;

//浮遊敵を管理するクラス
class Enemy_Fly : public EnemyBase
{
    int hModel_;                        // モデル番号

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