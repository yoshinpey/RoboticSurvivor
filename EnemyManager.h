
#pragma once
#include <vector>
#include <random>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト
    GameObject* pParent_;

    // 乱数生成器の初期化
    std::mt19937 InitializeRandomGenerator();

    // 範囲内のランダムな座標を選択
    // 引数:乱数, 座標の最小値, 座標の最大値
    XMFLOAT3 GenerateRandomPosition(std::mt19937& mt, XMFLOAT3 minPosition, XMFLOAT3 maxPosition);

    // ランダムな敵の種類を選択
    // 引数:乱数, 生成リストから選択する敵のリスト
    EnemyType GenerateRandomEnemyType(std::mt19937& mt, const std::vector<EnemyType>& includeList);
public:
    EnemyManager(GameObject* parent);
    ~EnemyManager();

    // エネミーの生成を行う
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // 指定したenemyTypeに一致するエネミーだけ全削除する
    void RemoveEnemy(EnemyType enemyType);

    // 生存していないエネミーをリストから削除する
    void RemoveDeadEnemies(EnemyBase* enemy);

    // すべてのエネミーの削除を行う
    void RemoveAllEnemies();

    // 指定した範囲内に指定したエネミーを複数体生成する
    // minPosition  : スポーン位置の最小値(X, Y, Z)
    // maxPosition  : スポーン位置の最大値(X, Y, Z)
    // spawnCount   : 生成数
    // enemyType    : 生成するエネミーの種類
    void SpawnMultiEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 0,0,0 },
        int spawnCount = 1,
        EnemyType enemyType = EnemyType::MAX
    );

    // 指定した範囲内にランダムなエネミーを生成する
    // minPosition  : スポーン位置の最小値(X, Y, Z)
    // maxPosition  : スポーン位置の最大値(X, Y, Z)
    // spawnCount   : 生成数
    // includeList  : 生成リストから選択する敵の種類リスト
    void SpawnRandomMultiEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 0,0,0 },
        int spawnCount = 1,
        const std::vector<EnemyType>&includeList = {}
    );

    // 指定したenemyTypeに一致するエネミーの総数を取得する
    int GetEnemyCount(EnemyType enemyType = EnemyType::MAX);

    // エネミーリストを取得する
    std::vector<EnemyBase*> GetEnemyList() { return enemies; }
};