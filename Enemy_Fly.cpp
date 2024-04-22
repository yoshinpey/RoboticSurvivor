#include "Enemy_Fly.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 0.0f, 0.0f };      // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // モデルの回転
}

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pPlayer_(nullptr)
{
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Fly", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Fly", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Fly", "attackCooldown", 0, "Settings/EnemySettings.ini");
    status_.maxHp_                      = GetPrivateProfileFloat("Enemy_Fly", "maxHp", 0, "Settings/EnemySettings.ini");
    status_.collisionScale_             = GetPrivateProfileFloat("Enemy_Fly", "collisionScale", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Fly", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Fly", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Fly", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Fly", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Fly::~Enemy_Fly()
{
}

void Enemy_Fly::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Enemy/Enemy_Fly.fbx");
    assert(hModel_ >= 0);

    // 当たり判定付与
    SphereCollider* pCollision = new SphereCollider(collisionPosition, status_.collisionScale_);
    AddCollider(pCollision);

    transform_.rotate_.y = modelRotate.y;

    currentHp_ = status_.maxHp_;    // 現在のHPを最大値で初期化
}

void Enemy_Fly::Update()
{
    // HPがなければ死亡
    if (IsDead()) KillMe();

    // プレイヤーへの方向ベクトル(正規化済)
    XMFLOAT3 directionToPlayer = CheckPlayerDirection();

    // プレイヤーとの内積を計算して視界角度を取得
    float dotProduct = CalculateDotProduct(directionToPlayer);
    const float fovAngle = XMConvertToRadians(1.0f);

    // プレイヤーが視界内にいる場合
    if (dotProduct >= fovAngle)
    {
        // 許可された距離までプレイヤーに接近
        if (algorithm_.attackDistance_ <= CheckPlayerDistance())
        {
            ApproachPlayer(directionToPlayer);
        }

        // プレイヤーの方向を向くように視界を回転
        RotateTowardsPlayer(directionToPlayer);
    }
}

void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Fly::Release()
{
}

void Enemy_Fly::OnCollision(GameObject* pTarget)
{
    // 銃弾に当たったとき
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        // EnemyBaseにキャスト
        BulletBase* pBullet = dynamic_cast<BulletBase*>(pTarget);
        // ダメージを与える
        DecreaseHp(pBullet->GetBulletParameter().damage_);

        // 貫通しない場合は弾丸を消す
        if (pBullet->GetBulletParameter().isPenetration_ == 0) pBullet->KillMe();
        else;//////貫通する場合、初回ヒットか判定して一回だけダメージ与えるようにする
    }
}

void Enemy_Fly::Attack()
{
}

void Enemy_Fly::IncreaseHp(float amount)
{
    currentHp_ += amount;
    if (currentHp_ > status_.maxHp_) {
        currentHp_ = status_.maxHp_;
    }
}

void Enemy_Fly::DecreaseHp(float amount)
{
    currentHp_ -= amount;
    if (currentHp_ < 0) {
        currentHp_ = 0;
    }
}