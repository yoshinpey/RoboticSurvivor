#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Enemy_Explosion.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"


namespace
{
    const std::string modelName = "Enemy/Enemy_Explosion.fbx";    // モデル名
    const XMFLOAT3 collisionOffset = { 0.0f, 1.0f, 0.0f };        // 当たり判定の位置
    const XMFLOAT3 modelRotate = { 0.0f, 0.0f, 0.0f };            // モデルの回転
    const float deltaTime = 0.05f;                                // ダメージのシェーダーの変化量

    // モデルのアニメーション
    struct AnimFrame
    {
        int startFrame = 0;
        int endFrame = 100;
        float speed = 0.75f;
    }anim;
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1)
{
    // INIファイルからデータを構造体へ流し込む
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_                         = GetPrivateProfileFloat("Enemy_Explosion", "maxHp", 0, "Settings/EnemySettings.ini");
    commonStatus_.currentHp_                     = commonStatus_.maxHp_;        // 現在のHPを最大値で初期化

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
    // エネミーマネージャーのリストから死んだエネミーを削除する
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Explosion::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load(modelName);
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
    pastPosition_ = transform_.position_;

    // 許可された距離までプレイヤーに接近
    if (enemyAlgorithm_.attackDistance_ <= CheckPlayerDistance())
    {
        ApproachPlayer(CheckPlayerDirection());
    }

    // プレイヤーの方向を向くように視界を回転
    RotateTowardsPlayer(CheckPlayerDirection());
}

void Enemy_Explosion::Draw()
{
    // ダメージシェーダーの適応処理
    if (damageTime_ > 0) damageTime_ -= deltaTime;
    Direct3D::damageTime = damageTime_;
    
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
        BulletHit();
    }

    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // エネミーベースにキャスト
        EnemyBase* pEnemy = static_cast<EnemyBase*>(pTarget);
        CollisionDetectionWithEnemy(pEnemy);
    }
};

void Enemy_Explosion::Attack()
{
}