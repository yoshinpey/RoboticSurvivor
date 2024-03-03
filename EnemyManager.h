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

    // �����_���Ȉʒu�ƃ^�C�v�ŃG�l�~�[�𐶐�����
    // �w�肵���G�l�~�[�^�C�v���w�肵��3D���W�͈͓̔��ɃX�|�[��������
    // enemyType: �X�|�[�����������G�l�~�[�̃^�C�v
    // minPosition: �X�|�[���ʒu�̍ŏ��l(X, Y, Z)
    // maxPosition: �X�|�[���ʒu�̍ő�l(X, Y, Z)
    // spawnCount: ��������G�l�~�[�̐�
    void SpawnRandomEnemy(EnemyType enemyType, XMFLOAT3 minPosition, XMFLOAT3 maxPosition, int spawnCount);

};
