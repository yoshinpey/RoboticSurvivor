#pragma once
#include <vector>
#include <string>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // �G�l�~�[�̃��X�g

public:
    EnemyManager();
    ~EnemyManager();

    // �G�l�~�[�̐����Ɣz�u���s�����\�b�h
    void SpawnEnemy(const XMFLOAT3& spawnPosition, const std::string& name, int id);

    // �G�l�~�[�̍X�V���s�����\�b�h
    void UpdateEnemies();

    // �G�l�~�[�̍폜���s�����\�b�h
    void RemoveEnemy(EnemyBase* enemy);

    // �G�l�~�[�̐����擾���郁�\�b�h
    size_t GetEnemyCount() const;

    // �G�l�~�[�̑S�폜���s�����\�b�h
    void RemoveAllEnemies();

    // �����_���Ȉʒu�ɃG�l�~�[�𐶐����郁�\�b�h
    void SpawnRandomEnemy();

    // �G�l�~�[�̑S�̂��ꊇ�X�V���郁�\�b�h
    void UpdateAllEnemies();

    // ���O��ID����G�l�~�[���擾���郁�\�b�h
    EnemyBase* GetEnemyByNameAndId(const std::string& name, int id);
};
