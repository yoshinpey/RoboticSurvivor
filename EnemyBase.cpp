#include "EnemyBase.h"
#include "Player.h"

namespace
{
    float rotateSpeed = 0.03f;      // 体の回転スピード
    float damageTime = 1.0f;        // ダメージを受けた時のシェーダーの適応時間
    const float deltaTime = 0.05f;  // ダメージのシェーダーの変化量
}

// コンストラクタの実装
EnemyBase::EnemyBase(GameObject* parent, EnemyType enemyType, std::string name)
    : Character(parent, name), enemyType_(enemyType), damageTime_(0.0f)
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

// 銃弾が当たった時の処理
void EnemyBase::BulletHit()
{
    //ダメージシェーダーの適応時間をセットする
    damageTime_ = damageTime;
}

// 敵同士の当たり判定処理
void EnemyBase::CollisionDetectionWithEnemy(EnemyBase* pEnemy)
{
//    // ぶつかった対象の半径サイズを調べる
//    float selfScale = enemyStatus_.collisionScale_;                  // 自身の半径
//    float enemyScale = pEnemy->GetEnemyStatus().collisionScale_;     // 対象の半径
//
//    // ぶつかった対象の位置を求める
//    XMFLOAT3 selfPos = transform_.position_;        // 自身の位置
//    XMFLOAT3 targetPos = pEnemy->GetPosition();     // 対象の位置
//
//    // ぶつかった対象の方向を調べる
//    XMFLOAT3 targetDir = CalculateDirection(targetPos, selfPos);
//
//    // ぶつかった対象との距離を調べる
//    float pushDist = CalculateDistance(targetPos, selfPos);
//
//    // 重なり量 ＝ 2体の半径の合算値 - 距離
//    float overlap = (selfScale + enemyScale) - pushDist;
//
//    // 重なり量があったら計算
//    if (overlap > 0)
//    {
//        // 重なり量を半分にして、双方を均等に押し出す
//        overlap *= 0.5f;
//
//        // 押し出し距離
//        XMVECTOR pushBackVec = XMLoadFloat3(&targetDir) * overlap;
//
//        // 対象を押し出す
//        XMVECTOR newTargetPos = XMLoadFloat3(&targetPos) + pushBackVec;
//        XMStoreFloat3(&targetPos, newTargetPos);
//        pEnemy->SetPosition(targetPos);
//
//        // 自身を押し出す
//        XMVECTOR newSelfPos = XMLoadFloat3(&selfPos) - pushBackVec;
//        XMStoreFloat3(&selfPos, newSelfPos);
//        transform_.position_ = selfPos;
//    }

    // 自身と対象の半径を取得
    float selfScale = enemyStatus_.collisionScale_;
    float enemyScale = pEnemy->GetEnemyStatus().collisionScale_;

    // 自身と対象の位置を取得
    XMVECTOR selfPos = XMLoadFloat3(&transform_.position_);
    XMFLOAT3 fPos = pEnemy->GetPosition();
    XMVECTOR targetPos = XMLoadFloat3(&fPos);

    // 自身と対象の距離ベクトルを計算
    XMVECTOR dir = targetPos - selfPos;

    // 距離の平方を計算
    float distSq = XMVectorGetX(XMVector3LengthSq(dir));
    float radiusSum = selfScale + enemyScale;

    // 半径の合計の平方と距離の平方を比較
    if (distSq < radiusSum * radiusSum)
    {
        // 重なり量を計算
        float dist = sqrt(distSq);
        float overlap = (radiusSum - dist) * 0.5f;

        // 距離が0の場合を避けるためにチェック
        if (dist > 0)
        {
            // 押し出しベクトルを計算して適用
            XMVECTOR pushVec = dir / dist * overlap;
            selfPos -= pushVec;
            targetPos += pushVec;
        }
        else
        {
            // 距離が0の場合、任意の方向に押し出す
            XMVECTOR pushVec = XMVectorSet(overlap, 0.0f, 0.0f, 0.0f);
            selfPos -= pushVec;
            targetPos += pushVec;
        }

        // 結果を反映
        XMStoreFloat3(&transform_.position_, selfPos);
        XMFLOAT3 newTargetPos;
        XMStoreFloat3(&newTargetPos, targetPos);
        pEnemy->SetPosition(newTargetPos);
    }
}

// ダメージシェーダーの前処理）
void EnemyBase::PreDrawDamageShader()
{
    if (damageTime_ > 0) {
        damageTime_ -= deltaTime;
    }
    Direct3D::damageTime = damageTime_;
}

// ダメージシェーダーの後処理）
void EnemyBase::PostDrawDamageShader()
{
    Direct3D::damageTime = 0.0f;
}