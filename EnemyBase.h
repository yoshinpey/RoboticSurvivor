#pragma once
#include "Engine/GameObject.h"
#include "Player.h"

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
    EnemyType enemyType_;  // エネミーの種類
    
    // 各ステータス
    struct EnemyStatus
    {
        float walkSpeed_;       // 移動速度
        int attackPower_;       // 攻撃力
        int attackCooldown_;    // 攻撃頻度
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
    EnemyStatus status_;
    EnemyAlgorithm algorithm_;


public:
    EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
        : GameObject(parent, name), enemyType_(enemyType)
    {
        status_ = { 0,0,0 };
        algorithm_ = { 0,0,0,0 };    

    }

    virtual ~EnemyBase() = default;

    // 敵の種類を取得
    EnemyType GetEnemyType() const { return enemyType_; }

    // 攻撃
    virtual void Attack() = 0;

    // プレイヤーとの距離を算出する
    float CheckPlayerDistance() {
        Player* pPlayer_ = static_cast<Player*>(FindObject("Player"));
        return CalculateDistance(this->GetPosition(), pPlayer_->GetPosition());

    }

    // プレイヤーへの方向を算出する
    virtual XMFLOAT3 CheckPlayerDirection() = 0;

    // 内積計算(視野角計算)
    virtual float CalculateDotProduct(const XMFLOAT3& directionToPlayer) = 0;

    // 移動速度に応じた移動量でプレイヤーに接近する
    virtual void ApproachPlayer(const XMFLOAT3& directionToPlayer) = 0;

    // 敵の体をプレイヤーの方向へ回転させる
    virtual void RotateTowardsPlayer(const XMFLOAT3& directionToPlayer) = 0;
};