#include "EnemyBase.h"
#include "Player.h"

namespace
{
    float rotateSpeed = 0.03f;      // 体の回転スピード
    float damageTime = 1.0f;        // ダメージを受けた時のシェーダーの適応時間
}

// コンストラクタの実装
EnemyBase::EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
    : Character(parent, name), enemyType_(enemyType)
{
}

// プレイヤーとの距離を算出する
float EnemyBase::CheckPlayerDistance()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    if (!pPlayer)return 0.0f;
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    XMFLOAT3 enePos = this->GetPosition();
    return CalculateDistance(plaPos, enePos);
}

// プレイヤーへの方向を算出する
XMFLOAT3 EnemyBase::CheckPlayerDirection()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    if (!pPlayer)return { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    XMFLOAT3 enePos = this->GetPosition();
    return CalculateDirection(plaPos, enePos);
}

// 移動速度に応じた移動量でプレイヤーに接近する
void EnemyBase::ApproachPlayer(const XMFLOAT3& directionToPlayer)
{
    // 移動ベクターをエネミーのポジションに加算する
    XMFLOAT3 moveVector = { directionToPlayer.x * commonParameter_.walkSpeed_, 0, directionToPlayer.z * commonParameter_.walkSpeed_ };
    transform_.position_ = CalculateFloat3Add(transform_.position_, moveVector);
}

// 敵の体をプレイヤーの方向へ回転させる
void EnemyBase::RotateTowardsPlayer(const XMFLOAT3& directionToPlayer)
{
    // プレイヤーへの逆ベクトル(向かせたい方向)
    XMVECTOR playerBackward = XMVector3Normalize(XMVectorSet(directionToPlayer.x, 0, directionToPlayer.z, 0));

    // エネミーが向いている方向
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR enemyForward = XMVector3Normalize(XMVectorSet(sinf(rotY), 0, cosf(rotY), 0));

    // 内積と外積を計算
    float dot = XMVectorGetX(XMVector3Dot(enemyForward, playerBackward));
    XMVECTOR cross = XMVector3Cross(enemyForward, playerBackward);

    // 角度を計算して回転
    float angle = static_cast<float>(atan2(XMVectorGetY(cross), dot));
    transform_.rotate_.y += XMConvertToDegrees(angle) * rotateSpeed;
}

void EnemyBase::BulletHit()
{
    damageTime_ = damageTime;
}

// 敵同士の当たり判定処理
void EnemyBase::CollisionDetectionWithEnemy(EnemyBase* pEnemy)
{
    // ぶつかった対象の半径サイズを調べる
    float selfScale = enemyStatus_.collisionScale_;                  // 自身の半径
    float enemyScale = pEnemy->GetEnemyStatus().collisionScale_;     // 対象の半径

    // ぶつかった対象の位置を求める
    XMFLOAT3 selfPos = transform_.position_;        // 自身の位置
    XMFLOAT3 targetPos = pEnemy->GetPosition();     // 対象の位置

    // ぶつかった対象の方向を調べる
    XMFLOAT3 targetDir = CalculateDirection(targetPos, selfPos);

    // ぶつかった対象との距離を調べる
    float pushDist = CalculateDistance(targetPos, selfPos);

    // 重なり量 ＝ 2体の半径の合算値 - 距離
    float overlap = (selfScale + enemyScale) - pushDist;

    // 重なり量があったら計算
    if (overlap > 0)
    {
        // 重なり量を半分にして、双方を均等に押し出す
        overlap *= 0.5f;

        // 押し出し距離
        XMVECTOR pushBackVec = XMLoadFloat3(&targetDir) * overlap;

        // 対象を押し出す
        XMVECTOR newTargetPos = XMLoadFloat3(&targetPos) + pushBackVec;
        XMStoreFloat3(&targetPos, newTargetPos);
        pEnemy->SetPosition(targetPos);

        // 自身を押し出す
        XMVECTOR newSelfPos = XMLoadFloat3(&selfPos) - pushBackVec;
        XMStoreFloat3(&selfPos, newSelfPos);
        transform_.position_ = selfPos;
    }
}