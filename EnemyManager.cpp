#include "EnemyManager.h"

#include "Enemy_Ground.h"
#include "Enemy_Fly.h"
#include "Enemy_Explosion.h"


EnemyManager::EnemyManager(GameObject* parent) : pParent_(parent), pNewEnemy_(nullptr)
{
}

EnemyManager::~EnemyManager()
{
    // �G�l�~�[�̉��(�Q�[���I�u�W�F�N�g�ł���Ă邩��f���[�g�͕s�v)
    enemies.clear();
}

void EnemyManager::SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType)
{
    switch (enemyType)
    {
    case EnemyType::FLY:
        pNewEnemy_ = Instantiate<Enemy_Fly>(pParent_);
        pNewEnemy_->SetPosition(spawnPosition);
        break;

    case EnemyType::GROUND:
        pNewEnemy_ = Instantiate<Enemy_Ground>(pParent_);
        pNewEnemy_->SetPosition(spawnPosition);
        break;

    case EnemyType::EXPLOSION:
        pNewEnemy_ = Instantiate<Enemy_Explosion>(pParent_);
        pNewEnemy_->SetPosition(spawnPosition);
        //static_cast<Enemy_Explosion*>(pNewEnemy_)->SetPosition(spawnPosition);
        break;
    case EnemyType::MAX:
        return;
    }
    enemies.push_back(pNewEnemy_);
}

void EnemyManager::RemoveEnemy(EnemyType enemyType)
{
    // �w�肵��enemyType�Ɉ�v����G�l�~�[�����S�폜����
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            (*it)->KillMe();        // �G�l�~�[�I�u�W�F�N�g���폜����
            it = enemies.erase(it); // �G�l�~�[�����X�g����폜
        }
        else
        {
            ++it; // ���̗v�f�ɐi��
        }
    }
}

void EnemyManager::RemoveAllEnemies()
{
    // �S�ẴG�l�~�[�I�u�W�F�N�g���폜����
    for (auto enemy : enemies)
    {
        enemy->KillMe();
    }
    // �G�l�~�[���X�g���N���A����
    enemies.clear(); 
}

std::mt19937 EnemyManager::InitializeRandomGenerator()
{
    std::random_device rd;
    return std::mt19937(rd());
}

XMFLOAT3 EnemyManager::GenerateRandomPosition(std::mt19937& mt, XMFLOAT3 minPosition, XMFLOAT3 maxPosition)
{
    // �͈͓��̃����_���ȍ��W�𐶐�
    std::uniform_real_distribution<float> distPosX(minPosition.x, maxPosition.x);
    std::uniform_real_distribution<float> distPosY(minPosition.y, maxPosition.y);
    std::uniform_real_distribution<float> distPosZ(minPosition.z, maxPosition.z);

    return XMFLOAT3(distPosX(mt), distPosY(mt), distPosZ(mt));
}

EnemyType EnemyManager::GenerateRandomEnemyType(std::mt19937& mt, EnemyType excludeType)
{
    std::uniform_int_distribution<int> distType(0, static_cast<int>(EnemyType::MAX) - 1);
    EnemyType spawnEnemyType;

    // ���O����^�C�v���w�肳��Ă���΍đI��
    do
    {
        spawnEnemyType = static_cast<EnemyType>(distType(mt));
    } 
    while (spawnEnemyType == excludeType);

    return spawnEnemyType;
}

void EnemyManager::SpawnMultiEnemy(XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount, EnemyType enemyType)
{
    // ����������
    std::mt19937 mt = InitializeRandomGenerator();

    for (int i = 0; i < spawnCount; ++i) 
    {
        // �ʒu������
        XMFLOAT3 spawnPosition = GenerateRandomPosition(mt, minPosition, maxPosition);
        SpawnEnemy(spawnPosition, enemyType);
    }
}

void EnemyManager::SpawnRandomMultiEnemy(XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount, EnemyType excludeType)
{
    // ����������
    std::mt19937 mt = InitializeRandomGenerator();

    for (int i = 0; i < spawnCount; ++i) 
    {
        EnemyType spawnEnemyType = GenerateRandomEnemyType(mt, excludeType);

        // �ʒu������
        XMFLOAT3 spawnPosition = GenerateRandomPosition(mt, minPosition, maxPosition);
        SpawnEnemy(spawnPosition, spawnEnemyType);
    }
}