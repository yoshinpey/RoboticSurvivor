#include "EnemyManager.h"
#include "Enemy_Ground.h"
#include "Enemy_Fly.h"
#include "GameManager.h"

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
    EnemyBase* pNewEnemy = nullptr;

    switch (enemyType)
    {
    case EnemyType::FLY:
        pNewEnemy = Instantiate<Enemy_Fly>(pParent_);
        static_cast<Enemy_Fly*>(pNewEnemy)->SetPosition(spawnPosition);
        break;

    case EnemyType::GROUND:
        pNewEnemy = Instantiate<Enemy_Ground>(pParent_);
        static_cast<Enemy_Ground*>(pNewEnemy)->SetPosition(spawnPosition);
        break;

        ///////////////一旦別のやつで代用
    case EnemyType::EXPLOSION:
        pNewEnemy = Instantiate<Enemy_Ground>(pParent_);
        static_cast<Enemy_Ground*>(pNewEnemy)->SetPosition(spawnPosition);
        break;
    }

    if (pNewEnemy != nullptr)
    {
        enemies.push_back(pNewEnemy);
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

