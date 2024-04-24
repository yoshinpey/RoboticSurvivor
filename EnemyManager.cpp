
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

void EnemyManager::Update()
{
    // エネミーの状態をチェックし、削除する
    //RemoveDeadEnemies();
}

// 生存していないエネミーを削除するメソッド
void EnemyManager::RemoveDeadEnemies()
{
    // リスト内のエネミーをループしてチェック
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->IsDead()) {
            // エネミーが死亡している場合は削除
            delete* it;
            (*it)->KillMe();
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }
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
    // 指定したenemyTypeに一致するエネミーだけ全削除する
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            (*it)->KillMe();        // エネミーオブジェクトを削除する
            it = enemies.erase(it); // エネミーをリストから削除
        }
        else
        {
            ++it; // 次の要素に進む
        }
    }
}

void EnemyManager::RemoveEnemyOne(EnemyType enemyType)
{
    // 指定したenemyTypeに一致するエネミーだけ全削除する
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
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
    // 範囲内のランダムな座標を生成
    std::uniform_real_distribution<float> distPosX(minPosition.x, maxPosition.x);
    std::uniform_real_distribution<float> distPosY(minPosition.y, maxPosition.y);
    std::uniform_real_distribution<float> distPosZ(minPosition.z, maxPosition.z);

    return XMFLOAT3(distPosX(mt), distPosY(mt), distPosZ(mt));
}

EnemyType EnemyManager::GenerateRandomEnemyType(std::mt19937& mt, EnemyType excludeType, const std::vector<EnemyType>& excludeList)
{
    std::uniform_int_distribution<int> distType(0, static_cast<int>(EnemyType::MAX) - 1);

    // 選択候補リストの作成
    std::vector<EnemyType> candidateTypes = {};
    for (int i = 0; i < static_cast<int>(EnemyType::MAX); ++i)
    {
        EnemyType type = static_cast<EnemyType>(i);
        if (type != excludeType && std::find(excludeList.begin(), excludeList.end(), type) == excludeList.end())
        {
            candidateTypes.push_back(type);
        }
    }

    // 除外される候補がない場合は除外リストを無視してランダムに選択
    if (candidateTypes.empty())
    {
        return static_cast<EnemyType>(distType(mt));
    }

    // ランダムにエネミータイプを選択
    int index = distType(mt) % candidateTypes.size();
    return candidateTypes[index];
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

void EnemyManager::SpawnRandomMultiEnemy(XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount,
    EnemyType excludeType, const std::vector<EnemyType>& excludeList)
{
    // 乱数生成器
    std::mt19937 mt = InitializeRandomGenerator();

    for (int i = 0; i < spawnCount; ++i)
    {
        // ランダムな敵の種類を選択
        EnemyType spawnEnemyType = GenerateRandomEnemyType(mt, excludeType);

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
        return (int)enemies.size();
    }

    // 指定されたエネミーの個体数を返す
    int count = 0;
    for (auto enemy : enemies)
    {
        if (enemy->GetEnemyType() == enemyType) count++;
    }
    return count;
}