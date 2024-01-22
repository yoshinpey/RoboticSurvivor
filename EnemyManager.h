#pragma once
#include <vector>
#include <string>
#include "EnemyBase.h"
#include "Enemy_Ground.h"
#include "Enemy_Fly.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // �G�l�~�[�̃��X�g

public:
    // �R���X�g���N�^
    EnemyManager();

    // �f�X�g���N�^
    ~EnemyManager();

    // �G�l�~�[�̐������s�����\�b�h
    void SpawnEnemy(const XMFLOAT3& spawnPosition, EnemyType enemyType);

    // �G�l�~�[�̍폜���s�����\�b�h
    void RemoveEnemy(EnemyType enemyType);

    // �G�l�~�[�̑S�폜���s�����\�b�h
    void RemoveAllEnemies();
};
