#include "EnemyManager.h"
#include <time.h>

EnemyManager::EnemyManager()
{
    // 乱数の初期化
    srand(static_cast<unsigned>(time(nullptr)));
}

EnemyManager::~EnemyManager()
{
    // エネミーの解放
    for (auto enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

void EnemyManager::SpawnEnemy(const XMFLOAT3& spawnPosition, EnemyType enemyType)
{
    switch (enemyType)
    {
    // case EnemyType::FLY:
        // enemies.push_back(new Enemy_Fly(spawnPosition));
        // break;
    case EnemyType::GROUND:
        enemies.push_back(new Enemy_Ground(spawnPosition));
        break;
    }
}

void EnemyManager::RemoveEnemy(EnemyType enemyType)
{
    auto it = std::remove_if(enemies.begin(), enemies.end(),
        [enemyType](const EnemyBase* enemy) { return enemy->GetEnemyType() == enemyType; });
    for (auto iter = it; iter != enemies.end(); ++iter)
    {
        delete* iter;
    }
    enemies.erase(it, enemies.end());
}


void EnemyManager::RemoveAllEnemies()
{
    for (auto enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

