#pragma once
#include "EnemyBase.h"
#include <vector>

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト
    GameObject* pParent_;
public:
    EnemyManager(GameObject* parent);
    ~EnemyManager();

    // エネミーの生成を行う
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // 指定したenemyTypeに一致するエネミーだけ全削除する
    void RemoveEnemy(EnemyType enemyType);

    // すべてのエネミーの削除を行う
    void RemoveAllEnemies();

};
