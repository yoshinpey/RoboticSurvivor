
#include "EnemyManager.h"

#include "Enemy_Ground.h"
#include "Enemy_Fly.h"
#include "Enemy_Explosion.h"


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
        pNewEnemy = InstantiateFront<Enemy_Fly>(pParent_);
        break;

    case EnemyType::GROUND:
        pNewEnemy = InstantiateFront<Enemy_Ground>(pParent_);
        break;

    case EnemyType::EXPLOSION:
        pNewEnemy = InstantiateFront<Enemy_Explosion>(pParent_);
        break;

    case EnemyType::MAX:
        return;
    }
    pNewEnemy->SetPosition(spawnPosition);
    enemies.push_back(pNewEnemy);
}

void EnemyManager::RemoveEnemy(EnemyType enemyType)
{
    // 指定したenemyTypeに一致するエネミーを全削除する
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            (*it)->KillMe();        // エネミー本体を削除
            it = enemies.erase(it); // エネミーをリストから削除
        }
        else
        {
            ++it; // 次の要素に進む
        }
    }
}

void EnemyManager::RemoveDeadEnemies(EnemyBase* enemy)
{
    // 死亡したエネミーをマネージャー内のリストから削除する
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it) == enemy)
        {
            it = enemies.erase(it); // エネミーをリストから削除
            return;
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

std::mt19937 EnemyManager::InitializeRandomGenerator()
{
    std::random_device rd;
    return std::mt19937(rd());
}

XMFLOAT3 EnemyManager::GenerateRandomPosition(std::mt19937& mt, XMFLOAT3 minPosition, XMFLOAT3 maxPosition)
{
    // もし大小関係が不正だった場合、正しい順序に並べ替える
    if (minPosition.x > maxPosition.x) std::swap(minPosition.x, maxPosition.x);
    if (minPosition.y > maxPosition.y) std::swap(minPosition.y, maxPosition.y);
    if (minPosition.z > maxPosition.z) std::swap(minPosition.z, maxPosition.z);

    // 範囲内のランダムな座標を生成
    std::uniform_real_distribution<float> distPosX(minPosition.x, maxPosition.x);
    std::uniform_real_distribution<float> distPosY(minPosition.y, maxPosition.y);
    std::uniform_real_distribution<float> distPosZ(minPosition.z, maxPosition.z);

    return XMFLOAT3(distPosX(mt), distPosY(mt), distPosZ(mt));
}

EnemyType EnemyManager::GenerateRandomEnemyType(std::mt19937& mt, const std::vector<EnemyType>& includeList)
{
    // リストが空の場合は無効
    if (includeList.empty()) return EnemyType::MAX;

    std::uniform_int_distribution<int> distType(0, static_cast<int>(includeList.size()) - 1);
    int index = distType(mt);
    return includeList[index];
}

void EnemyManager::SpawnMultiEnemy(XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount, EnemyType enemyType)
{
    // 乱数生成器
    std::mt19937 mt = InitializeRandomGenerator();

    for (int i = 0; i < spawnCount; ++i)
    {
        // 位置を決定
        XMFLOAT3 spawnPosition = GenerateRandomPosition(mt, minPosition, maxPosition);
        SpawnEnemy(spawnPosition, enemyType);
    }
}

void EnemyManager::SpawnRandomMultiEnemy(XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount, const std::vector<EnemyType>& includeList)
{
    // リストが空の場合は無効
    if (includeList.empty()) return;
    
    // 乱数生成器
    std::mt19937 mt = InitializeRandomGenerator();

    for (int i = 0; i < spawnCount; ++i)
    {
        // ランダムな敵の種類を選択
        EnemyType spawnEnemyType = GenerateRandomEnemyType(mt, includeList);

        // 位置を決定
        XMFLOAT3 spawnPosition = GenerateRandomPosition(mt, minPosition, maxPosition);
        SpawnEnemy(spawnPosition, spawnEnemyType);
    }
}

int EnemyManager::GetEnemyCount(EnemyType enemyType)
{
    // 引数指定がないとき
    if (enemyType == EnemyType::MAX) 
    {
        // エネミーの総数を返す
        return static_cast<int>(enemies.size());
    }

    // 指定されたエネミーの個体数を返す
    int count = 0;
    for (auto enemy : enemies)
    {
        if (enemy->GetEnemyType() == enemyType) ++count;
    }
    return count;
}