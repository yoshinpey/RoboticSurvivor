#include "EnemyManager.h"

#include "Enemy_Ground.h"
#include "Enemy_Fly.h"
#include "Enemy_Explosion.h"
#include <random>


EnemyManager::EnemyManager(GameObject* parent) : pParent_(parent), pNewEnemy_(nullptr)
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
    case EnemyType::FLY:
        pNewEnemy_ = Instantiate<Enemy_Fly>(pParent_);
        static_cast<Enemy_Fly*>(pNewEnemy_)->SetPosition(spawnPosition);
        break;

    case EnemyType::GROUND:
        pNewEnemy_ = Instantiate<Enemy_Ground>(pParent_);
        static_cast<Enemy_Ground*>(pNewEnemy_)->SetPosition(spawnPosition);
        break;

        ///////////////一旦別のやつで代用中
    case EnemyType::EXPLOSION:
        pNewEnemy_ = Instantiate<Enemy_Explosion>(pParent_);
        static_cast<Enemy_Explosion*>(pNewEnemy_)->SetPosition(spawnPosition);
        break;
    }

    if (pNewEnemy_ != nullptr)
    {
        enemies.push_back(pNewEnemy_);
    }
}

void EnemyManager::RemoveEnemy(EnemyType enemyType)
{
    // 指定したenemyTypeに一致するエネミーだけ全削除する
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            (*it)->KillMe();        // エネミーオブジェクトを削除する
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

void EnemyManager::SpawnMultiEnemy(EnemyType enemyType, XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<float> distPosX(minPosition.x, maxPosition.x);
    std::uniform_real_distribution<float> distPosY(minPosition.y, maxPosition.y);
    std::uniform_real_distribution<float> distPosZ(minPosition.z, maxPosition.z);

    for (int i = 0; i < spawnCount; ++i) {
        // ランダムに位置を決定
        XMFLOAT3 spawnPosition = XMFLOAT3(distPosX(mt), distPosY(mt), distPosZ(mt));

        // 指定されたエネミータイプでエネミーをスポーン
        SpawnEnemy(spawnPosition, enemyType);
    }
}


void EnemyManager::SpawnRandomEnemy(XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount, EnemyType excludeType)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<float> distPosX(minPosition.x, maxPosition.x);
    std::uniform_real_distribution<float> distPosY(minPosition.y, maxPosition.y);
    std::uniform_real_distribution<float> distPosZ(minPosition.z, maxPosition.z);
    std::uniform_int_distribution<int> distType(0, static_cast<int>(EnemyType::MAX) - 1); // EnemyType::MAXは最大値を示す仮定の値

    for (int i = 0; i < spawnCount; ++i) {
        EnemyType spawnEnemyType;
        do {
            spawnEnemyType = static_cast<EnemyType>(distType(mt)); // ランダムにエネミータイプを選択
        } while (spawnEnemyType == excludeType); // 除外するタイプが指定されていれば再選択

        XMFLOAT3 spawnPosition = XMFLOAT3(distPosX(mt), distPosY(mt), distPosZ(mt));

        // 指定されたエネミータイプでエネミーをスポーン
        SpawnEnemy(spawnPosition, spawnEnemyType);
    }
}