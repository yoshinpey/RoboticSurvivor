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

    // ウェーブの追加
    void AddWave(const WaveData& wave);

    // ウェーブの開始
    void StartWaves();

    // ウェーブの停止
    void StopWaves();

    // ウェーブの更新
    void Update();

    // ウェーブがアクティブかどうかを返す
    bool IsWaveActive() const;
};

