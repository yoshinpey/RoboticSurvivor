#include "EnemySpawn.h"
#include <random>

#include "Player.h"


// コンストラクタの実装
EnemySpawn::EnemySpawn(EnemyManager* enemyManager, Player* player, int waveTimer, int maxWaves)
    : enemyManager_(enemyManager), player_(player), waveTimer_(waveTimer), waveCount_(0), maxWaves_(maxWaves) {}

// ウェーブのスポーン処理の実装
void EnemySpawn::SpawnWave() {
    // ランダムな位置に敵をスポーンさせる
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(-20.0f, 20.0f);
    std::uniform_real_distribution<float> disZ(-20.0f, 20.0f);

    // ランダムな位置を計算
    XMFLOAT3 spawnPosition(disX(gen), 0.0f, disZ(gen));

    // ランダムな種類の敵をスポーンさせる
    EnemyType enemyType = static_cast<EnemyType>(rand() % static_cast<int>(EnemyType::MAX));

    // 敵をスポーンさせる
    enemyManager_->SpawnEnemy(spawnPosition, enemyType);
}

// ウェーブの更新処理の実装
void EnemySpawn::UpdateWave() {
    waveTimer_--; // タイマーを減らす

    // タイマーが0以下になったら新しいウェーブをスタート
    if (waveTimer_ <= 0) {
        SpawnWave(); // ウェーブをスポーンさせる
        waveCount_++; // ウェーブカウントを増やす
        waveTimer_ = 300; // タイマーをリセット

        // 最大ウェーブ数に達したら処理を終了
        if (waveCount_ >= maxWaves_) {
            // 何かしらの処理
            return;
        }
    }
}
