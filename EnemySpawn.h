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

    // JSON�t�@�C������G�̏o���f�[�^��ǂݍ��݁A�G�𐶐�����
    void SpawnEnemies();
};
