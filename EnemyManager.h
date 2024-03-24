#pragma once
#include <vector>
#include <random>
#include "EnemyBase.h"

class EnemyManager
{
private:
    std::vector<EnemyBase*> enemies;  // エネミーのリスト
    GameObject* pParent_;
    EnemyBase* pNewEnemy_;

    // 乱数生成器の初期化
    std::mt19937 InitializeRandomGenerator();

    // 範囲内のランダムな座標を選択
    // 引数:乱数, 座標の最小値, 座標の最大値
    XMFLOAT3 GenerateRandomPosition(std::mt19937& mt, XMFLOAT3 minPosition, XMFLOAT3 maxPosition);

    // ランダムな敵の種類を選択
    // 引数:乱数, 生成リストから除外する敵(あれば), 生成リストから除外する敵のリスト(あれば)
    EnemyType GenerateRandomEnemyType(std::mt19937& mt, EnemyType excludeType = EnemyType::MAX, const std::vector<EnemyType>& excludeList = {});
public:
    EnemyManager(GameObject* parent);
    ~EnemyManager();

    // エネミーの生成を行う
    void SpawnEnemy(XMFLOAT3 spawnPosition, EnemyType enemyType);

    // 指定したenemyTypeに一致するエネミーだけ全削除する
    void RemoveEnemy(EnemyType enemyType);

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
    // excludeType  : 生成リストから除外する敵の種類単体(あれば指定)
    // excludeList  : 生成リストから除外する敵の種類リスト(あれば指定)
    void SpawnRandomMultiEnemy
    (
        XMFLOAT3 minPosition = { 0,0,0 },
        XMFLOAT3 maxPosition = { 0,0,0 },
        int spawnCount = 1,
        EnemyType excludeType = EnemyType::MAX,
        const std::vector<EnemyType>& excludeList = {}
     );

    // エネミーの総数を取得する
    int GetEnemyCount() { return static_cast<int>(enemies.size()); }

    // 指定したenemyTypeに一致するエネミーの総数を取得する
    int GetEnemyCount(EnemyType enemyType);
};
