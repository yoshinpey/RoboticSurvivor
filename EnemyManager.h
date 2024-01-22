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
    GameObject* parent_;
    const XMFLOAT3& spawnPosition_;
public:
    // �R���X�g���N�^
    EnemyManager();

    // �f�X�g���N�^
    ~EnemyManager();

    // �G�l�~�[�̐����Ɣz�u���s�����\�b�h
    void SpawnEnemy(const XMFLOAT3& spawnPosition, EnemyType enemyType);

    // �G�l�~�[�̍X�V���s�����\�b�h
    void UpdateEnemies();

    // �G�l�~�[�̍폜���s�����\�b�h
    void RemoveEnemy(EnemyBase* enemy);

    // �G�l�~�[�̐����擾���郁�\�b�h
    size_t GetEnemyCount() const;

    // �G�l�~�[�̑S�폜���s�����\�b�h
    void RemoveAllEnemies();

    // ���O��ID����G�l�~�[���擾���郁�\�b�h
    EnemyBase* GetEnemyByNameAndId(const std::string& name, int id);
};
