#pragma once
#include <vector>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // �G�l�~�[�̃��X�g
    GameObject* pParent_;
    EnemyBase* pNewEnemy_;
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
    // enemyType: �G�l�~�[�̎��
    // minPosition: �X�|�[���ʒu�̍ŏ��l(X, Y, Z)
    // maxPosition: �X�|�[���ʒu�̍ő�l(X, Y, Z)
    // spawnCount: ������
    void SpawnMultiEnemy
    (
        EnemyType enemyType = EnemyType::GROUND, 
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 10,10,10 },
        int spawnCount = 1
    );

    // �w�肵���͈͓��Ƀ����_���ȃG�l�~�[�𐶐�����
    // minPosition: �X�|�[���ʒu�̍ŏ��l(X, Y, Z)
    // maxPosition: �X�|�[���ʒu�̍ő�l(X, Y, Z)
    // spawnCount: ������
    // excludeType: ���O����G�l�~�[�̎��
    void SpawnRandomEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 10,10,10 },
        int spawnCount = 1,
        EnemyType excludeType = EnemyType::MAX
    );
};
