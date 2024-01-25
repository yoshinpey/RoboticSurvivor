#pragma once
#include <vector>
#include <string>
#include "EnemyBase.h"



class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト
    GameObject* pParent_;
    XMFLOAT3 spawnPosition_;
public:
    // コンストラクタ
    EnemyManager(GameObject* parent);

    // デストラクタ
    ~EnemyManager();

    // エネミーの生成を行うメソッド
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // エネミーの削除を行うメソッド
    void RemoveEnemy(EnemyType enemyType);

    // エネミーの全削除を行うメソッド
    void RemoveAllEnemies();

    XMFLOAT3 GetSpawnPosition_()
    {
        return spawnPosition_;
    }
};
