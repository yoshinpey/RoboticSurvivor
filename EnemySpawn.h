#pragma once

#include "EnemyManager.h"
class Player;

class EnemySpawn 
{
private:
    EnemyManager* enemyManager_; // 敵を管理するEnemyManagerへのポインタ
    Player* player_;             // プレイヤーオブジェクトへのポインタ
    int waveTimer_;              // ウェーブの間隔を表すタイマー
    int waveCount_;              // 現在のウェーブカウント
    int maxWaves_;               // 最大ウェーブ数

public:
    // コンストラクタ
    EnemySpawn(EnemyManager* enemyManager, Player* player, int waveTimer, int maxWaves);

    // ウェーブのスポーン処理
    void SpawnWave();

    // ウェーブの更新処理
    void UpdateWave();
};
