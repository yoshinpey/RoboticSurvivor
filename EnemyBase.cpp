#include "EnemyBase.h"
#include "Player.h"

namespace
{
    float rotateSpeed = 0.03f;
}

// コンストラクタの実装
EnemyBase::EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
    : GameObject(parent, name), enemyType_(enemyType), currentHp_(0.0f)
{
    status_ = { 0,0,0,0 };
    algorithm_ = { 0,0,0,0 };
}

// プレイヤーとの距離を算出する
float EnemyBase::CheckPlayerDistance()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    XMFLOAT3 enePos = this->GetPosition();
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    return CalculateDistance(enePos, plaPos);
}

// プレイヤーへの方向を算出する
XMFLOAT3 EnemyBase::CheckPlayerDirection()
{
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    XMFLOAT3 enePos = this->GetPosition();
    XMFLOAT3 plaPos = pPlayer->GetPosition();
    return CalculateDirection(enePos, plaPos);
}

// 内積計算(視野角計算)
float EnemyBase::CalculateDotProduct(const XMFLOAT3& directionToPlayer)
{
    // エネミーが向いている方向
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR enemyForward = XMVector3Normalize(XMVectorSet(sinf(rotY), 0, cosf(rotY), 0));

    // プレイヤーへの方向ベクトルとの内積を計算して視界角度を取得
    float dotProduct;
    XMStoreFloat(&dotProduct, XMVector3Dot(enemyForward, XMLoadFloat3(&directionToPlayer)));
    return acosf(dotProduct);
}

// 移動速度に応じた移動量でプレイヤーに接近する
void EnemyBase::ApproachPlayer(const XMFLOAT3& directionToPlayer)
{
    // 移動ベクターをエネミーのポジションに加算する
    XMFLOAT3 moveVector = { directionToPlayer.x * status_.walkSpeed_, 0, directionToPlayer.z * status_.walkSpeed_ };
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
