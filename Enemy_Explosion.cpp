#include "Enemy_Explosion.h"

namespace
{
    float collisionScale = 2.0f;                            // 当たり判定の大きさ
    XMFLOAT3 collisionPosition = { 0.0f, 1.0f, 0.0f };      // 当たり判定の位置
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1), pCollision_(nullptr)
{
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Explosion", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Explosion", "attackCooldown", 0, "Settings/EnemySettings.ini");

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Explosion", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Explosion", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Explosion", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Explosion", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Explosion::~Enemy_Explosion()
{
}

void Enemy_Explosion::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load("Character/Enemy_Explosion.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // 当たり判定付与
    pCollision_ = new SphereCollider(collisionPosition, collisionScale);
    AddCollider(pCollision_);
}

void Enemy_Explosion::Update()
{
    // 爆発でコライダーを拡大する
    //pCollision_->SetRadius(transform_.scale_.x);
}

void Enemy_Explosion::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy_Explosion::Release()
{
}

void Enemy_Explosion::OnCollision(GameObject* pTarget)
{
    // 銃弾に当たったとき
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        KillMe();
    }
}

void Enemy_Explosion::Attack()
{
}
