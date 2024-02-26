#include "Enemy_Ground.h"

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1), pCollision_(nullptr), lastAngle_(0)
{
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Ground", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Ground", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Ground", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Ground", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Ground::~Enemy_Ground()
{
}

void Enemy_Ground::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load("Character/Enemy_02.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // 当たり判定付与
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 2.0f);
    AddCollider(pCollision_);

}

void Enemy_Ground::Update()
{
    // プレイヤーの向いている方向
    //float rotY = pPlayer_->GetRotate().y;

    // エネミーの向いている方向
    XMFLOAT3 charaFoword;
    charaFoword.x = (float)sin(XMConvertToRadians(transform_.rotate_.y));
    charaFoword.z = (float)cos(XMConvertToRadians(transform_.rotate_.y));

    // 正規化
    /////////////////////////ここ

    // エネミーの視界角度（半角）
    const float fovAngle = XMConvertToRadians(180.0f);

    // プレイヤーが視界内にいるかどうかを判定
    XMFLOAT3 toPlayer = CheckPlayerDirection();
    XMVECTOR vecToPlayer = XMLoadFloat3(&toPlayer);

    float dotProduct;
    XMStoreFloat(&dotProduct, XMVector3Dot(XMLoadFloat3(&transform_.rotate_), vecToPlayer));

    if (dotProduct >= cos(fovAngle / 2))
    {
        transform_.scale_.y = 0.2f;
        // プレイヤーが視界内にいる場合の処理を記述
        // プレイヤーまでの距離を計算
        float dist = CheckPlayerDistance();

        // プレイヤー位置までの方向ベクトルを計算
        XMFLOAT3 direction = CheckPlayerDirection();
        
        // 移動速度に応じて移動量を計算
        XMFLOAT3 moveVector = { direction.x * status_.walkSpeed_, 0, direction.z * status_.walkSpeed_ };

        // 新しい位置を計算
        if (algorithm_.approachDistance_ <= dist)
        {
            transform_.position_ = CalculateFloat3Add(transform_.position_, moveVector);

            // エネミーをプレイヤーの方向に向ける
            float newAngle = atan2(direction.z, direction.x);
            float angleDiff = newAngle - lastAngle_;
            if (angleDiff > XM_PI)
            {
                newAngle -= XM_2PI;
            }
            else if (angleDiff < -XM_PI)
            {
                newAngle += XM_2PI;
            }
            transform_.rotate_.y = -XMConvertToDegrees(newAngle);
            lastAngle_ = newAngle;

            OutputDebugString(std::to_string(dist).c_str());
            OutputDebugString("\n");
        }
    }
    else
        transform_.scale_.y = 1.0f;
}

void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{
    /*
    // 銃弾に当たったとき
    if (pTarget->GetObjectName() == "Bullet")
    {
        //KillMe();
    }
    */
}

void Enemy_Ground::Attack()
{
}

