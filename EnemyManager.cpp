#include "EnemyManager.h"

EnemyManager::EnemyManager(GameObject* parent) : pParent_(parent)
{
}

EnemyManager::~EnemyManager()
{
    // エネミーの解放(ゲームオブジェクトでやってるからデリートは不要)
    enemies.clear();
}

void EnemyManager::SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType)
{
    switch (enemyType)
    {
    // case EnemyType::FLY:
        // enemies.push_back(new Enemy_Fly(spawnPosition));
        // break;
    case EnemyType::GROUND:
        enemies.push_back(Instantiate<Enemy_Ground>(pParent_));
        break;
    }
}

void EnemyManager::RemoveEnemy(EnemyType enemyType)
{
    auto it = std::remove_if(enemies.begin(), enemies.end(),
        [enemyType](EnemyBase* enemy) { return enemy->GetEnemyType() == enemyType; });
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

