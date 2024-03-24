#pragma once
#include <vector>
#include <random>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // �G�l�~�[�̃��X�g
    GameObject* pParent_;
    EnemyBase* pNewEnemy_;

    // ����������̏�����
    std::mt19937 InitializeRandomGenerator();

    // �͈͓��̃����_���ȍ��W��I��
    // ����:����, ���W�̍ŏ��l, ���W�̍ő�l
    XMFLOAT3 GenerateRandomPosition(std::mt19937& mt, XMFLOAT3 minPosition, XMFLOAT3 maxPosition);

    // �����_���ȓG�̎�ނ�I��
    // ����:����, �������X�g���珜�O����G(�����), �������X�g���珜�O����G�̃��X�g(�����)
    EnemyType GenerateRandomEnemyType(std::mt19937& mt, EnemyType excludeType = EnemyType::MAX, const std::vector<EnemyType>& excludeList = {});
public:
    EnemyManager(GameObject* parent);
    ~EnemyManager();

    // �G�l�~�[�̐������s��
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // �w�肵��enemyType�Ɉ�v����G�l�~�[�����S�폜����
    void RemoveEnemy(EnemyType enemyType);

    // ���ׂẴG�l�~�[�̍폜���s��
    void RemoveAllEnemies();

    // �w�肵���͈͓��Ɏw�肵���G�l�~�[�𕡐��̐�������
    // minPosition  : �X�|�[���ʒu�̍ŏ��l(X, Y, Z)
    // maxPosition  : �X�|�[���ʒu�̍ő�l(X, Y, Z)
    // spawnCount   : ������
    // enemyType    : ��������G�l�~�[�̎��
    void SpawnMultiEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 0,0,0 },
        int spawnCount = 1, 
        EnemyType enemyType = EnemyType::MAX
    );

    // �w�肵���͈͓��Ƀ����_���ȃG�l�~�[�𐶐�����
    // minPosition  : �X�|�[���ʒu�̍ŏ��l(X, Y, Z)
    // maxPosition  : �X�|�[���ʒu�̍ő�l(X, Y, Z)
    // spawnCount   : ������
    // excludeType  : �������X�g���珜�O����G�̎�ޒP��(����Ύw��)
    // excludeList  : �������X�g���珜�O����G�̎�ރ��X�g(����Ύw��)
    void SpawnRandomMultiEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 0,0,0 },
        int spawnCount = 1,
        EnemyType excludeType = EnemyType::MAX,
        const std::vector<EnemyType>& excludeList = {}
     );

    // �G�l�~�[�̑������擾����
    int GetEnemyCount() { return static_cast<int>(enemies.size()); }

    // �w�肵��enemyType�Ɉ�v����G�l�~�[�̑������擾����
    int GetEnemyCount(EnemyType enemyType);
};
