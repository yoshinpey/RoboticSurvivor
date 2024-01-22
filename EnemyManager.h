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
    GameObject* parent_;
    const XMFLOAT3& spawnPosition_;
public:
    // コンストラクタ
    EnemyManager();

    // デストラクタ
    ~EnemyManager();

    // エネミーの生成と配置を行うメソッド
    void SpawnEnemy(const XMFLOAT3& spawnPosition, EnemyType enemyType);

    // エネミーの更新を行うメソッド
    void UpdateEnemies();

    // エネミーの削除を行うメソッド
    void RemoveEnemy(EnemyBase* enemy);

    // エネミーの数を取得するメソッド
    size_t GetEnemyCount() const;

    // エネミーの全削除を行うメソッド
    void RemoveAllEnemies();

    // 名前とIDからエネミーを取得するメソッド
    EnemyBase* GetEnemyByNameAndId(const std::string& name, int id);
};
