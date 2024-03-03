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
    // �G�l�~�[�̉��(�Q�[���I�u�W�F�N�g�ł���Ă邩��f���[�g�͕s�v)
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

        ///////////////��U�ʂ̂�ő�p��
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
    // �w�肵��enemyType�Ɉ�v����G�l�~�[�����S�폜����
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            (*it)->KillMe();        // �G�l�~�[�I�u�W�F�N�g���폜����
            it = enemies.erase(it); // �G�l�~�[�����X�g����폜���A���̗v�f���w���C�e���[�^���擾����
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

void EnemyManager::SpawnMultiEnemy(EnemyType enemyType, XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<float> distPosX(minPosition.x, maxPosition.x);
    std::uniform_real_distribution<float> distPosY(minPosition.y, maxPosition.y);
    std::uniform_real_distribution<float> distPosZ(minPosition.z, maxPosition.z);

    for (int i = 0; i < spawnCount; ++i) {
        // �����_���Ɉʒu������
        XMFLOAT3 spawnPosition = XMFLOAT3(distPosX(mt), distPosY(mt), distPosZ(mt));

        // �w�肳�ꂽ�G�l�~�[�^�C�v�ŃG�l�~�[���X�|�[��
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
    std::uniform_int_distribution<int> distType(0, static_cast<int>(EnemyType::MAX) - 1); // EnemyType::MAX�͍ő�l����������̒l

    for (int i = 0; i < spawnCount; ++i) {
        EnemyType spawnEnemyType;
        do {
            spawnEnemyType = static_cast<EnemyType>(distType(mt)); // �����_���ɃG�l�~�[�^�C�v��I��
        } while (spawnEnemyType == excludeType); // ���O����^�C�v���w�肳��Ă���΍đI��

        XMFLOAT3 spawnPosition = XMFLOAT3(distPosX(mt), distPosY(mt), distPosZ(mt));

        // �w�肳�ꂽ�G�l�~�[�^�C�v�ŃG�l�~�[���X�|�[��
        SpawnEnemy(spawnPosition, spawnEnemyType);
    }
}