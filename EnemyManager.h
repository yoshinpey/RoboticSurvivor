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

    // �G�l�~�[�̐������s�����\�b�h
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // �G�l�~�[�̍폜���s�����\�b�h
    void RemoveEnemy(EnemyType enemyType);

    // �G�l�~�[�̑S�폜���s�����\�b�h
    void RemoveAllEnemies();

    XMFLOAT3 GetSpawnPosition_()
    {
        return spawnPosition_;
    }
};
