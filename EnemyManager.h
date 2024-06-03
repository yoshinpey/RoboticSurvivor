
#pragma once
#include <vector>
#include <random>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // �G�l�~�[�̃��X�g
    GameObject* pParent_;

    // ����������̏�����
    std::mt19937 InitializeRandomGenerator();

    // �͈͓��̃����_���ȍ��W��I��
    // ����:����, ���W�̍ŏ��l, ���W�̍ő�l
    XMFLOAT3 GenerateRandomPosition(std::mt19937& mt, XMFLOAT3 minPosition, XMFLOAT3 maxPosition);

    // �����_���ȓG�̎�ނ�I��
    // ����:����, �������X�g����I������G�̃��X�g
    EnemyType GenerateRandomEnemyType(std::mt19937& mt, const std::vector<EnemyType>& includeList);
public:
    EnemyManager(GameObject* parent);
    ~EnemyManager();

    // �G�l�~�[�̐������s��
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // �w�肵��enemyType�Ɉ�v����G�l�~�[�����S�폜����
    void RemoveEnemy(EnemyType enemyType);

    // �������Ă��Ȃ��G�l�~�[�����X�g����폜����
    void RemoveDeadEnemies(EnemyBase* enemy);

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
    // includeList  : �������X�g����I������G�̎�ރ��X�g
    void SpawnRandomMultiEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 0,0,0 },
        int spawnCount = 1,
        const std::vector<EnemyType>&includeList = {}
    );

    // �w�肵��enemyType�Ɉ�v����G�l�~�[�̑������擾����
    int GetEnemyCount(EnemyType enemyType = EnemyType::MAX);

    // �G�l�~�[���X�g���擾����
    std::vector<EnemyBase*> GetEnemyList() { return enemies; }
};