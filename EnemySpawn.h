#pragma once
#include "jsonReader.h"

class EnemyManager;

struct WaveData
{
    int enemyCount;           // 出現させる敵の数
    EnemyType enemyType;      // 出現させる敵の種類
    XMFLOAT3 minPosition;     // 出現させる敵の最小座標
    XMFLOAT3 maxPosition;     // 出現させる敵の最大座標
};

class EnemySpawn 
{
private:
    EnemyManager* pEnemyManager_; // 敵を管理するEnemyManagerへのポインタ

    // ウェーブごとに敵を生成する
    void SpawnEnemiesForWave(const nlohmann::json& waveData);

public:
    EnemySpawn(EnemyManager* enemyManager);
    ~EnemySpawn();

    // JSONファイルから敵の出現データを読み込み、敵を生成する
    void SpawnEnemiesFromJSON(const std::string& filename);
};
