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
    EnemyBase(EnemyType enemyType)
        : GameObject(), enemyType_(enemyType)
    {
    }

    virtual ~EnemyBase() = 0;
    virtual void Update() = 0;

    // エネミーの種類を取得
    EnemyType GetEnemyType() const { return enemyType_; }

    virtual std::string GetName() const = 0;
    virtual int GetId() const = 0;
};