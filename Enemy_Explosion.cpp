#include "Enemy_Explosion.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

#include "Engine/Direct3D.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 1.0f, 0.0f };        // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 0.0f, 0.0f };          // モデルの回転
    struct AnimFrame
    {
        int startFrame = 0;
        int endFrame = 100;
        float speed = 0.75f;
    };
    AnimFrame anim;
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1), damageTime(0.0f)
{
    // INIファイルからデータを構造体へ流し込む
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_                         = GetPrivateProfileFloat("Enemy_Explosion", "maxHp", 0, "Settings/EnemySettings.ini");
    commonStatus_.currentHp_ = commonStatus_.maxHp_;

    enemyStatus_.attackPower_                = GetPrivateProfileInt("Enemy_Explosion", "attackPower", 0, "Settings/EnemySettings.ini");
    enemyStatus_.attackCooldown_             = GetPrivateProfileInt("Enemy_Explosion", "attackCooldown", 0, "Settings/EnemySettings.ini");
    enemyStatus_.collisionScale_             = GetPrivateProfileFloat("Enemy_Explosion", "collisionScale", 0, "Settings/EnemySettings.ini");

    enemyAlgorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Explosion", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Explosion", "patrolRadius", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Explosion", "approachDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Explosion", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Explosion::~Enemy_Explosion()
{
    // エネミーのマネージャーリストから死んだエネミーを削除する
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Explosion::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load("Enemy/Enemy_Explosion.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, anim.startFrame, anim.endFrame, anim.speed);

    // 当たり判定付与
    SphereCollider* pCollision = new SphereCollider(collisionOffset, enemyStatus_.collisionScale_);
    AddCollider(pCollision);

    // モデルの回転
    transform_.rotate_.y = modelRotate.y;


}

void Enemy_Explosion::Update()
{
    // 現在地を保存する
    currentPosition_ = transform_.position_;

    // 許可された距離までプレイヤーに接近
    float dist = CheckPlayerDistance();
    if (enemyAlgorithm_.attackDistance_ <= dist)
    {
        ApproachPlayer(CheckPlayerDirection());
    }

    // プレイヤーの方向を向くように視界を回転
    RotateTowardsPlayer(CheckPlayerDirection());
}

void Enemy_Explosion::Draw()
{
    if (damageTime > 0.0f) damageTime -= 0.05f;
    Direct3D::damageTime = damageTime;
    
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Direct3D::damageTime = 0.0f;
}

void Enemy_Explosion::Release()
{
}

void Enemy_Explosion::OnCollision(GameObject* pTarget)
{
    // 銃弾に当たったとき
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        damageTime = 1.0f;
    }

    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        transform_.position_ = currentPosition_;
    }
};

void Enemy_Explosion::Attack()
{
}