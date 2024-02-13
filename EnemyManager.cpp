#include "EnemyManager.h"
#include "Enemy_Ground.h"
#include "Enemy_Fly.h"
#include "GameManager.h"

EnemyManager::EnemyManager(GameObject* parent) : pParent_(parent)
{
}

EnemyManager::~EnemyManager()
{
    // �G�l�~�[�̉��(�Q�[���I�u�W�F�N�g�ł���Ă邩��f���[�g�͕s�v)
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

        ///////////////��U�ʂ̂�ő�p
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
    // �w�肵��enemyType�Ɉ�v����G�l�~�[�����S�폜����
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            (*it)->KillMe(); // �G�l�~�[�I�u�W�F�N�g���폜����
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