#pragma once
#include <vector>
#include <string>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト

public:
    EnemyManager();
    ~EnemyManager();

    // エネミーの生成と配置を行うメソッド
    void SpawnEnemy(const XMFLOAT3& spawnPosition, const std::string& name, int id);

    // エネミーの更新を行うメソッド
    void UpdateEnemies();

    // エネミーの削除を行うメソッド
    void RemoveEnemy(EnemyBase* enemy);

    // エネミーの数を取得するメソッド
    size_t GetEnemyCount() const;

    // エネミーの全削除を行うメソッド
    void RemoveAllEnemies();

    // ランダムな位置にエネミーを生成するメソッド
    void SpawnRandomEnemy();

    // エネミーの全体を一括更新するメソッド
    void UpdateAllEnemies();

    // 名前とIDからエネミーを取得するメソッド
    EnemyBase* GetEnemyByNameAndId(const std::string& name, int id);
};
