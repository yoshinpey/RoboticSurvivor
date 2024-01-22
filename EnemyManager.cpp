#include "EnemyManager.h"
#include <algorithm>
#include <cstdlib> // for rand() function
#include <ctime>   // for srand() function

EnemyManager::EnemyManager()
{
    // �����̏�����
    srand(static_cast<unsigned>(time(nullptr)));
}

EnemyManager::~EnemyManager()
{
    // �G�l�~�[�̉��
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
    // �����_���Ȉʒu�ɃG�l�~�[����
    float x = static_cast<float>(rand() % 10); // 0����10�͈̔͂Ń����_��
    float y = 0.0f;                             // �Œ�̍���
    float z = static_cast<float>(rand() % 10); // 0����10�͈̔͂Ń����_��

    XMFLOAT3 spawnPosition(x, y, z);

    // �����_���Ȗ��O��ID�����i���̎����j
    std::string name = "Enemy" + std::to_string(rand() % 100);
    int id = rand() % 100;

    // �G�l�~�[����
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
    return nullptr; // ������Ȃ��ꍇ��nullptr��Ԃ�
}
