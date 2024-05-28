#include "EnemySpawn.h"
#include <random>

#include "Player.h"
#include "EnemyManager.h"

// コンストラクタの実装
EnemySpawn::EnemySpawn(EnemyManager* enemyManager, Player* player, int waveTimer, int maxWaves)
    : enemyManager_(enemyManager), player_(player), waveTimer_(waveTimer), waveCount_(0), maxWaves_(maxWaves) {}

// ウェーブのスポーン処理の実装
void EnemySpawn::SpawnWave() {

}

// ウェーブの更新処理の実装
void EnemySpawn::UpdateWave() 
{
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
