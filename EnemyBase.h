#pragma once
#include "Engine/GameObject.h"

// エネミーの名前とIDを管理するenum
enum class EnemyType
{
    FLY,
    GROUND,
    EXPLOSION
};

// エネミーベースクラス
class EnemyBase : public GameObject
{
private:
    EnemyType enemyType_;  // エネミーの種類

public:
    // コンストラクタ
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
        : GameObject(parent, name), enemyType_(enemyType)
    {
    }

    virtual ~EnemyBase() = default;

    // エネミーの種類を取得
    EnemyType GetEnemyType() const { return enemyType_; }

    // 攻撃
    virtual void Attack() = 0;


    void detectPlayer() {
        // 視界内のプレイヤーを検出する処理
    }

    void pathfindToPlayer() {
        // プレイヤーに近づくための経路探索
    }

    void patrolInSightRange() {
        // 視界内での徘徊
    }

    void approachPlayer() {
        // プレイヤーに近づく
    }
};