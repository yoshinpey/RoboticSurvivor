//#include "EnemySpawn.h"
//#include "EnemyManager.h"
//#include "Player.h"
//
//EnemySpawn::EnemySpawn() 
//    :pEnemyManager_(nullptr), pPlayer_(nullptr), currentWaveIndex_(0), isWaveActive_(false)
//{
//    pEnemyManager_ = EnemyManager*
//    std::string filename = "EnemySpawn.json";
//    JsonReader::Load(filename);
//}
//
//EnemySpawn::~EnemySpawn()
//{
//}
//
//void EnemySpawn::AddWave(const WaveData& wave)
//{
//    waves_.push_back(wave);
//}
//
//void EnemySpawn::StartWaves()
//{
//    currentWaveIndex_ = 0;
//    isWaveActive_ = true;
//}
//
//void EnemySpawn::StopWaves()
//{
//    isWaveActive_ = false;
//}
//
//void EnemySpawn::Update()
//{
//    if (!isWaveActive_) return;
//
//    if (currentWaveIndex_ >= waves_.size())
//    {
//        isWaveActive_ = false;
//        return;
//    }
//
//    const WaveData& wave = waves_[currentWaveIndex_];
//
//    // waveDataから敵の出現データを取得し、EnemyManagerを使用して敵を生成する
//    pEnemyManager_->SpawnMultiEnemy(wave.minPosition, wave.maxPosition, wave.enemyCount, static_cast<EnemyType>(wave.enemyID));
//
//    ++currentWaveIndex_;
//}
//
//bool EnemySpawn::IsWaveActive() const
//{
//    return isWaveActive_;
//}
