#pragma once
#include "Engine/GameObject.h"

// エネミーの名前とIDを管理するenum
enum class EnemyType
{
    FLY,
    GROUND,
};

// エネミーベースクラス
class EnemyBase : public GameObject
{
private:
    EnemyType enemyType_;  // エネミーの種類

public:
    // コンストラクタ
    EnemyBase(GameObject* parent, EnemyType enemyType)
        : GameObject(parent), enemyType_(enemyType)
    {
    }

    virtual ~EnemyBase() = default;

    // エネミーの種類を取得
    EnemyType GetEnemyType() const { return enemyType_; }

    // 純粋仮想関数
    virtual void Update() = 0;
};