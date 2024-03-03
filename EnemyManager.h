#pragma once
#include <vector>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト
    GameObject* pParent_;
    EnemyBase* pNewEnemy_;
public:
    EnemyManager(GameObject* parent);
    ~EnemyManager();

    // エネミーの生成を行う
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // 指定したenemyTypeに一致するエネミーだけ全削除する
    void RemoveEnemy(EnemyType enemyType);

    // すべてのエネミーの削除を行う
    void RemoveAllEnemies();

    // 指定した範囲内に指定したエネミーを複数体生成する
    // enemyType: エネミーの種類
    // minPosition: スポーン位置の最小値(X, Y, Z)
    // maxPosition: スポーン位置の最大値(X, Y, Z)
    // spawnCount: 生成数
    void SpawnMultiEnemy
    (
        EnemyType enemyType = EnemyType::GROUND, 
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 10,10,10 },
        int spawnCount = 1
    );

    // 指定した範囲内にランダムなエネミーを生成する
    // minPosition: スポーン位置の最小値(X, Y, Z)
    // maxPosition: スポーン位置の最大値(X, Y, Z)
    // spawnCount: 生成数
    // excludeType: 除外するエネミーの種類
    void SpawnRandomEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 10,10,10 },
        int spawnCount = 1,
        EnemyType excludeType = EnemyType::MAX
    );
};
