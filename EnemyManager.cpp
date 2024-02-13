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
    // 指定したenemyTypeに一致するエネミーだけ全削除する
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            (*it)->KillMe(); // エネミーオブジェクトを削除する
            it = enemies.erase(it); // エネミーをリストから削除し、次の要素を指すイテレータを取得する
        }
        else
        {
            ++it; // 次の要素に進む
        }
    }
}

void EnemyManager::RemoveAllEnemies()
{
    // 全てのエネミーオブジェクトを削除する
    for (auto enemy : enemies)
    {
        enemy->KillMe();
    }
    // エネミーリストをクリアする
    enemies.clear(); 
}