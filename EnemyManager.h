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

    // ランダムな位置とタイプでエネミーを生成する
    // 指定したエネミータイプを指定した3D座標の範囲内にスポーンさせる
    // enemyType: スポーンさせたいエネミーのタイプ
    // minPosition: スポーン位置の最小値(X, Y, Z)
    // maxPosition: スポーン位置の最大値(X, Y, Z)
    // spawnCount: 生成するエネミーの数
    void SpawnRandomEnemy(EnemyType enemyType, XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount);

};
