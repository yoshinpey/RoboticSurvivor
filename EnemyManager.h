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
    EnemyManager();

    // デストラクタ
    ~EnemyManager();

    // エネミーの生成を行う
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // エネミーの削除を行う
    void RemoveEnemy(EnemyType enemyType);

    // エネミーの全削除を行う
    void RemoveAllEnemies();

    // エネミーの出現位置を取得する
    XMFLOAT3 GetSpawnPosition_() { return spawnPosition_; }

    // ゲームオブジェクトのセッタ
    void SetGameObject(GameObject* gameObject) { pParent_ = gameObject; }
};
