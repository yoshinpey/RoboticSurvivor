#pragma once
#include "Engine/GameObject.h"

// エネミーの名前とIDを管理するenum
enum class EnemyType
{
    FLY,
    GROUND,
    EXPLOSION,
    MAX
};

// エネミーベースクラス
class EnemyBase : public GameObject
{
private:

    // 各ステータス
    struct EnemyStatus
    {
        float walkSpeed_;       // 移動速度
        int attackPower_;       // 攻撃力
        int attackCooldown_;    // 攻撃頻度
        float maxHp_;           // 体力
    };

    // アルゴリズム
    struct EnemyAlgorithm
    {
        int detectPlayerDistance_;  // プレイヤーまでの距離
        int patrolRadius_;          // プレイヤーを検知する距離
        int approachDistance_;      // プレイヤーへ接近する距離
        int attackDistance_;        // プレイヤーへ攻撃を加える距離
    };

protected:
    // 構造体のインスタンス
    EnemyStatus status_;            // ステータス
    EnemyAlgorithm algorithm_;      // 行動
    EnemyType enemyType_;           // エネミーの種類
    float currentHp_;               // 現在のHP 

public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name);

    virtual ~EnemyBase() = default;

    // 敵の種類を取得
    EnemyType GetEnemyType() const { return enemyType_; }

    // 攻撃
    virtual void Attack() = 0;

    // プレイヤーとの距離を算出する
    float CheckPlayerDistance();

    // プレイヤーへの方向を算出する
    XMFLOAT3 CheckPlayerDirection();

    // 内積計算(視野角計算)
    float CalculateDotProduct(const XMFLOAT3& directionToPlayer);

    // 移動速度に応じた移動量でプレイヤーに接近する
    void ApproachPlayer(const XMFLOAT3& directionToPlayer);

    // 敵の体をプレイヤーの方向へ回転させる
    void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer);

    // HPを増やす
    void IncreaseHp(float amount);

    // HPを減らす
    void DecreaseHp(float amount);

    // 死亡判定
    bool IsDead() const { return currentHp_ <= 0; }
};