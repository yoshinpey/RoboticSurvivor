#pragma once
#include "Character.h"

// エネミーの名前とIDを管理するenum
enum class EnemyType
{
    FLY,
    GROUND,
    EXPLOSION,
    MAX
};

// エネミーベースクラス
class EnemyBase : public Character
{
private:
    // エネミーのステータス
    struct EnemyStatus
    {
        int attackPower_;       // 攻撃力
        int attackCooldown_;    // 攻撃頻度
        float collisionScale_;  // 当たり判定の大きさ
    };

    // エネミーのアルゴリズム
    struct EnemyAlgorithm
    {
        int detectPlayerDistance_;  // プレイヤーまでの距離
        int patrolRadius_;          // 巡回半径
        int approachDistance_;      // 接近距離
        int attackDistance_;        // 攻撃距離
    };

protected:

    // ダメージを受けた時のシェーダーの適応時間
    float damageTime_;

    EnemyStatus enemyStatus_;       // エネミーのステータス
    EnemyAlgorithm enemyAlgorithm_; // エネミーのアルゴリズム
    EnemyType enemyType_;           // エネミーの種類

public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name);

    virtual ~EnemyBase() = default;

    // 敵の種類を取得
    EnemyType GetEnemyType() const { return enemyType_; }

    // 敵のステータスを取得
    EnemyStatus GetEnemyStatus() const { return enemyStatus_; }

    // 敵のアルゴリズムを取得
    EnemyAlgorithm GetEnemyAlgorithm() const { return enemyAlgorithm_; }

    // 攻撃
    virtual void Attack() = 0;

    // プレイヤーとの距離を算出する
    float CheckPlayerDistance();

    // プレイヤーへの方向を算出する
    XMFLOAT3 CheckPlayerDirection();

    // 移動速度に応じた移動量でプレイヤーに接近する
    void ApproachPlayer(const XMFLOAT3& directionToPlayer);

    // 敵の体をプレイヤーの方向へ回転させる
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer);

    // 銃弾が当たった時の処理
    void BulletHit();

    // 敵同士の当たり判定処理
    void CollisionDetectionWithEnemy(EnemyBase* pEnemy);

    // ダメージシェーダーの適応処理（前処理）
    void PreDrawDamageShader();

    // ダメージシェーダーの適応処理（後処理）
    void PostDrawDamageShader();
};
