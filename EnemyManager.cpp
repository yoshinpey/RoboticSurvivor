
#include "EnemyManager.h"

#include "Enemy_Ground.h"
#include "Enemy_Fly.h"
#include "Enemy_Explosion.h"


EnemyManager::EnemyManager(GameObject* parent) : pParent_(parent)
{
}

EnemyManager::~EnemyManager()
{
    // �G�l�~�[�̉��(�Q�[���I�u�W�F�N�g�ł���Ă邩��f���[�g�͕s�v)
    enemies.clear();
}

void EnemyManager::Update()
{
    // �G�l�~�[�̏�Ԃ��`�F�b�N���A�폜����
    //RemoveDeadEnemies();
}

// �������Ă��Ȃ��G�l�~�[���폜���郁�\�b�h
void EnemyManager::RemoveDeadEnemies()
{
    // ���X�g���̃G�l�~�[�����[�v���ă`�F�b�N
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->IsDead()) {
            // �G�l�~�[�����S���Ă���ꍇ�͍폜
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

void EnemyManager::RemoveEnemyOne(EnemyType enemyType)
{
    // �w�肵��enemyType�Ɉ�v����G�l�~�[�����S�폜����
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if ((*it)->GetEnemyType() == enemyType)
        {
            it = enemies.erase(it); // �G�l�~�[�����X�g����폜
            return;
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

EnemyType EnemyManager::GenerateRandomEnemyType(std::mt19937& mt, EnemyType excludeType, const std::vector<EnemyType>& excludeList)
{
    std::uniform_int_distribution<int> distType(0, static_cast<int>(EnemyType::MAX) - 1);

    // �I����⃊�X�g�̍쐬
    std::vector<EnemyType> candidateTypes = {};
    for (int i = 0; i < static_cast<int>(EnemyType::MAX); ++i)
    {
        EnemyType type = static_cast<EnemyType>(i);
        if (type != excludeType && std::find(excludeList.begin(), excludeList.end(), type) == excludeList.end())
        {
            candidateTypes.push_back(type);
        }
    }

    // ���O������₪�Ȃ��ꍇ�͏��O���X�g�𖳎����ă����_���ɑI��
    if (candidateTypes.empty())
    {
        return static_cast<EnemyType>(distType(mt));
    }

    // �����_���ɃG�l�~�[�^�C�v��I��
    int index = distType(mt) % candidateTypes.size();
    return candidateTypes[index];
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

void EnemyManager::SpawnRandomMultiEnemy(XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount,
    EnemyType excludeType, const std::vector<EnemyType>& excludeList)
{
    // ����������
    std::mt19937 mt = InitializeRandomGenerator();

    for (int i = 0; i < spawnCount; ++i)
    {
        // �����_���ȓG�̎�ނ�I��
        EnemyType spawnEnemyType = GenerateRandomEnemyType(mt, excludeType);

        // �ʒu������
        XMFLOAT3 spawnPosition = GenerateRandomPosition(mt, minPosition, maxPosition);
        SpawnEnemy(spawnPosition, spawnEnemyType);
    }
}

int EnemyManager::GetEnemyCount(EnemyType enemyType)
{
    // �����w�肪�Ȃ��Ƃ�
    if (enemyType == EnemyType::MAX) 
    {
        return (int)enemies.size();
    }

    // �w�肳�ꂽ�G�l�~�[�̌̐���Ԃ�
    int count = 0;
    for (auto enemy : enemies)
    {
        if (enemy->GetEnemyType() == enemyType) count++;
    }
    return count;
}