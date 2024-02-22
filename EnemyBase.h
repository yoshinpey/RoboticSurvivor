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
    // 各ステータス
    struct EnemyStatus
    {
        float walkSpeed_;
        int attackPower_;
        int attackCooldown_;
    };

    // アルゴリズム
    struct EnemyAlgorithm
    {
        int ｄistance_;
        int patrolRadius_;
        int approachDistance_;
        int attackDistance_;
    };

protected:
    // 構造体のインスタンス
    EnemyStatus status_;
    EnemyAlgorithm algorithm_;
    
public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
        : GameObject(parent, name), enemyType_(enemyType)
    {
        status_ = { 0,0,0 };
        algorithm_ = { 0,0,0,0 };
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