#include "Enemy_Fly.h"

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1), pCollision_(nullptr)
{
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Fly", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Fly", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Fly", "attackCooldown", 0, "Settings/EnemySettings.ini");

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
    hModel_ = Model::Load("Character/Enemy.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 100, 0.75);

    // 当たり判定付与
    pCollision_ = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 1.5f);
    //pCollision_->SetObjectName
    AddCollider(pCollision_);

    //// 当たり判定付与
    //pHeadCollision_ = new SphereCollider(XMFLOAT3(0.0f, 3.0f, 0.0f), 5.0f);
    //AddHeadCollider(pHeadCollision_);

}

void Enemy_Fly::Update()
{
    // コリジョンの大きさをモデルに合わせる
    // pCollision_->SetRadius(transform_.scale_.x);
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
    if (pTarget->GetObjectName() == "Bullet")
    {
        transform_.scale_.y = 0.2f;
        //KillMe();
    }
}

//void Enemy_Fly::HeadOnCollision(GameObject* pTarget)
//{
//    // 銃弾に当たったとき
//    if (pTarget->GetObjectName() == "Bullet")
//    {
//        KillMe();
//    }
//}

void Enemy_Fly::Attack()
{
}

