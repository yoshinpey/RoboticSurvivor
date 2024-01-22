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
    case EnemyType::GROUND:
        enemies.push_back(new Enemy_Ground(parent_, spawnPosition));
        break;
    }
}
void EnemyManager::UpdateEnemies()
{
    for (auto enemy : enemies)
    {
        enemy->Update();
    }
}

void EnemyManager::RemoveEnemy(EnemyBase* enemy)
{
    auto it = std::remove(enemies.begin(), enemies.end(), enemy);
    enemies.erase(it, enemies.end());

    delete enemy;
}

size_t EnemyManager::GetEnemyCount() const
{
    return enemies.size();
}

void EnemyManager::RemoveAllEnemies()
{
    for (auto enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

EnemyBase* EnemyManager::GetEnemyByNameAndId(const std::string& name, int id)
{
    for (auto enemy : enemies)
    {
        if (enemy->GetName() == name && enemy->GetId() == id)
        {
            return enemy;
        }
    }
    return nullptr; // 見つからない場合はnullptrを返す
}