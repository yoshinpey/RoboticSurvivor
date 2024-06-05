#include "EnemySpawn.h"

#include "EnemyManager.h"
#include "Player.h"

EnemySpawn::EnemySpawn(EnemyManager* enemyManager, Player* player) : pEnemyManager_(enemyManager), pPlayer_(player)
{
    std::string filename = "EnemySpawn.json";
    JsonReader::Load(filename);
}

EnemySpawn::~EnemySpawn()
{
}

void EnemySpawn::SpawnEnemies()
{
    for (int waveIndex = 0; ; ++waveIndex)
    {
        std::string waveKey = "wave" + std::to_string(waveIndex);
        if (JsonReader::GetSection(waveKey).empty()) break;         // ウェーブが見つからない場合、読み込み終了
        auto waveData = JsonReader::GetSection(waveKey);

        // waveDataから敵の出現データを取得し、EnemyManagerを使用して敵を生成する
        int enemyID = waveData["enemyID"];
        int enemyCount = waveData["enemyCount"];
        auto minPosition = waveData["minPosition(X,Y,Z)"];
        auto maxPosition = waveData["maxPosition(X,Y,Z)"];

        // 敵の出現処理
        XMFLOAT3 minPos(minPosition[0], minPosition[1], minPosition[2]);
        XMFLOAT3 maxPos(maxPosition[0], maxPosition[1], maxPosition[2]);
        pEnemyManager_->SpawnMultiEnemy(minPos, maxPos, enemyCount, static_cast<EnemyType>(enemyID));
    }
}
