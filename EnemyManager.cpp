#include "EnemyManager.h"
#include <algorithm>
#include <cstdlib> // for rand() function
#include <ctime>   // for srand() function

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

void EnemyManager::SpawnEnemy(const XMFLOAT3& spawnPosition, const std::string& name, int id)
{
    EnemyBase* newEnemy = new EnemyBase(spawnPosition, name, id);
    enemies.push_back(newEnemy);
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

void EnemyManager::SpawnRandomEnemy()
{
    // ランダムな位置にエネミー生成
    float x = static_cast<float>(rand() % 10); // 0から10の範囲でランダム
    float y = 0.0f;                             // 固定の高さ
    float z = static_cast<float>(rand() % 10); // 0から10の範囲でランダム

    XMFLOAT3 spawnPosition(x, y, z);

    // ランダムな名前とID生成（仮の実装）
    std::string name = "Enemy" + std::to_string(rand() % 100);
    int id = rand() % 100;

    // エネミー生成
    SpawnEnemy(spawnPosition, name, id);
}

void EnemyManager::UpdateAllEnemies()
{
    for (auto enemy : enemies)
    {
        enemy->Update();
    }
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
