#pragma once
#include "jsonReader.h"
#include <functional>
#include <vector>

class EnemyManager;
class Player;

struct WaveData
{
    int enemyID;
    int enemyCount;
    XMFLOAT3 minPosition;
    XMFLOAT3 maxPosition;
};

class EnemySpawn
{
private:
    EnemyManager* pEnemyManager_;
    Player* pPlayer_;
    std::vector<WaveData> waves_;
    int currentWaveIndex_;
    bool isWaveActive_;

public:
    EnemySpawn(EnemyManager* enemyManager, Player* player);
    ~EnemySpawn();

    // �E�F�[�u�̒ǉ�
    void AddWave(const WaveData& wave);

    // �E�F�[�u�̊J�n
    void StartWaves();

    // �E�F�[�u�̒�~
    void StopWaves();

    // �E�F�[�u�̍X�V
    void Update();

    // �E�F�[�u���A�N�e�B�u���ǂ�����Ԃ�
    bool IsWaveActive() const;
};

