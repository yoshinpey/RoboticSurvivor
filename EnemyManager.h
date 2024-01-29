#pragma once
#include <vector>
#include <string>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト
    GameObject* pParent_;
public:
    // コンストラクタ
    EnemyManager(GameObject* parent);

    // デストラクタ
    ~EnemyManager();

    // エネミーの生成を行う
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // エネミーの削除を行う
    void RemoveEnemy(EnemyType enemyType);

    // エネミーの全削除を行う
    void RemoveAllEnemies();

};
