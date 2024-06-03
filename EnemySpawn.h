#pragma once
#include "jsonReader.h"

class EnemyManager;

struct WaveData
{
    int enemyCount;           // �o��������G�̐�
    EnemyType enemyType;      // �o��������G�̎��
    XMFLOAT3 minPosition;     // �o��������G�̍ŏ����W
    XMFLOAT3 maxPosition;     // �o��������G�̍ő���W
};

class EnemySpawn 
{
private:
    EnemyManager* pEnemyManager_; // �G���Ǘ�����EnemyManager�ւ̃|�C���^

    // �E�F�[�u���ƂɓG�𐶐�����
    void SpawnEnemiesForWave(const nlohmann::json& waveData);

public:
    EnemySpawn(EnemyManager* enemyManager);
    ~EnemySpawn();

    // JSON�t�@�C������G�̏o���f�[�^��ǂݍ��݁A�G�𐶐�����
    void SpawnEnemiesFromJSON(const std::string& filename);
};
