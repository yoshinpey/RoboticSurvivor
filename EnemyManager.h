#pragma once
#include <vector>
#include <string>
#include "EnemyBase.h"
#include "Enemy_Ground.h"
#include "Enemy_Fly.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト

public:
    // コンストラクタ
    EnemyManager();

    // デストラクタ
    ~EnemyManager();

    // エネミーの生成を行うメソッド
    void SpawnEnemy(const XMFLOAT3& spawnPosition, EnemyType enemyType);

    // エネミーの削除を行うメソッド
    void RemoveEnemy(EnemyType enemyType);

    // エネミーの全削除を行うメソッド
    void RemoveAllEnemies();
};
