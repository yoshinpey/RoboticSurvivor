#pragma once
#include "EnemyBase.h"
#include <vector>

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // �G�l�~�[�̃��X�g
    GameObject* pParent_;
public:
    EnemyManager(GameObject* parent);
    ~EnemyManager();

    // �G�l�~�[�̐������s��
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // �w�肵��enemyType�Ɉ�v����G�l�~�[�����S�폜����
    void RemoveEnemy(EnemyType enemyType);

    // ���ׂẴG�l�~�[�̍폜���s��
    void RemoveAllEnemies();

};
