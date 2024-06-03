#include "EnemySpawn.h"

#include "EnemyManager.h"

EnemySpawn::EnemySpawn(EnemyManager* enemyManager) : pEnemyManager_(enemyManager)
{
}

EnemySpawn::~EnemySpawn()
{
}


void EnemySpawn::SpawnEnemiesForWave(const nlohmann::json& waveData)
{
    // waveDataから敵の出現データを取得し、EnemyManagerを使用して敵を生成する処理を実装する
    // 例えば、waveDataから出したい敵IDや総数、最小座標、最大座標を取得し、EnemyManagerの適切な関数を呼び出す
    int enemyID = waveData["出したい敵ID"];
    int totalEnemies = waveData["出したい敵の総数"];
    auto minPosition = waveData["出したい敵の最小座標(XYZ)"];
    auto maxPosition = waveData["出したい敵の最大座標(XYZ)"];

    // 敵の出現処理
    XMFLOAT3 minPos(minPosition[0], minPosition[1], minPosition[2]);
    XMFLOAT3 maxPos(maxPosition[0], maxPosition[1], maxPosition[2]);
    pEnemyManager_->SpawnMultiEnemy(minPos, maxPos, totalEnemies, static_cast<EnemyType>(enemyID));
}

void EnemySpawn::SpawnEnemiesFromJSON(const std::string& filename)
{
    // JSONファイルからウェーブデータを読み込み、敵を生成する
    JsonReader::Load(filename);

    for (int waveIndex = 0; ; ++waveIndex)
    {
        std::string waveKey = "wave" + std::to_string(waveIndex);
        if (JsonReader::GetSection(waveKey).empty())
        {
            // ウェーブが見つからない場合、読み込み終了
            break;
        }
        SpawnEnemiesForWave(JsonReader::GetSection(waveKey));
    }
}