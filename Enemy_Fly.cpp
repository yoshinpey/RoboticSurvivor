#include "Enemy_Fly.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 0.0f, 0.0f };      // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // モデルの回転


    const float deltaTime = 0.05f;      // ダメージのシェーダーの変化量
}

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1)
{
    // INIファイルからデータを構造体へ流し込む
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Fly", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_                         = GetPrivateProfileFloat("Enemy_Fly", "maxHp", 0, "Settings/EnemySettings.ini");
    commonStatus_.currentHp_ = commonStatus_.maxHp_;        // 現在のHPを最大値で初期化

    enemyStatus_.attackPower_                = GetPrivateProfileInt("Enemy_Fly", "attackPower", 0, "Settings/EnemySettings.ini");
    enemyStatus_.attackCooldown_             = GetPrivateProfileInt("Enemy_Fly", "attackCooldown", 0, "Settings/EnemySettings.ini");
    enemyStatus_.collisionScale_             = GetPrivateProfileFloat("Enemy_Fly", "collisionScale", 0, "Settings/EnemySettings.ini");

    enemyAlgorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Fly", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Fly", "patrolRadius", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Fly", "approachDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Fly", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Fly::~Enemy_Fly()
{
    // エネミーのマネージャーリストから死んだエネミーを削除する
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Fly::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Enemy/Enemy_Fly.fbx");
    assert(hModel_ >= 0);

    // 当たり判定付与
    SphereCollider* pCollision = new SphereCollider(collisionPosition, enemyStatus_.collisionScale_);
    AddCollider(pCollision);

    transform_.rotate_.y = modelRotate.y;

}

void Enemy_Fly::Update()
{
    // プレイヤーへの方向ベクトル(正規化済)
    XMFLOAT3 directionToPlayer = CheckPlayerDirection();

    // 許可された距離までプレイヤーに接近
    if (enemyAlgorithm_.attackDistance_ <= CheckPlayerDistance())
    {
        ApproachPlayer(directionToPlayer);
    }

    // プレイヤーの方向を向くように視界を回転
    RotateTowardsPlayer(directionToPlayer);
}

void Enemy_Fly::Draw()
{
    // ダメージシェーダーの適応処理
    if (damageTime_ > 0) damageTime_ -= deltaTime;
    Direct3D::damageTime = damageTime_;

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Direct3D::damageTime = 0.0f;
}

void Enemy_Fly::Release()
{
}

void Enemy_Fly::OnCollision(GameObject* pTarget)
{
    // 銃弾に当たったとき
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        BulletHit();
    }


    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // エネミーベースにキャスト
        EnemyBase* pEnemy = static_cast<EnemyBase*>(pTarget);
        CollisionDetectionWithEnemy(pEnemy);
    }
}

void Enemy_Fly::Attack()
{
}
