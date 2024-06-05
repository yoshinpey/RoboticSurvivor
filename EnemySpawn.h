#pragma once
#include "jsonReader.h"

class EnemyManager;
class Player;

class EnemySpawn 
{
private:
    EnemyManager* pEnemyManager_;
    Player* pPlayer_;

public:
    EnemySpawn(EnemyManager* enemyManager, Player* player);
    ~EnemySpawn();

    // JSONファイルから敵の出現データを読み込み、敵を生成する
    void SpawnEnemies();
};
