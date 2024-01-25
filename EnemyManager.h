#pragma once
#include <vector>
#include <string>
#include "EnemyBase.h"



class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // �G�l�~�[�̃��X�g
    GameObject* pParent_;
    XMFLOAT3 spawnPosition_;
public:
    // �R���X�g���N�^
    EnemyManager(GameObject* parent);

    // �f�X�g���N�^
    ~EnemyManager();

    // �G�l�~�[�̐������s��
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // �G�l�~�[�̍폜���s��
    void RemoveEnemy(EnemyType enemyType);

    // �G�l�~�[�̑S�폜���s��
    void RemoveAllEnemies();

    // �G�l�~�[�̏o���ʒu���擾����
    XMFLOAT3 GetSpawnPosition_() { return spawnPosition_; }
};
