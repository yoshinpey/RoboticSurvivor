#include "Enemy_Fly.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 0.0f, 0.0f };      // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // モデルの回転
}

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), hModel_(-1)
{
    // INIファイルからデータを構造体へ流し込む
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Fly", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_                         = GetPrivateProfileFloat("Enemy_Fly", "maxHp", 0, "Settings/EnemySettings.ini");

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
    // 現在地を保存する
    currentPosition_ = transform_.position_;

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
        if (enemyAlgorithm_.attackDistance_ <= CheckPlayerDistance())
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
        // すでにこの敵に対してヒット済みの場合は無視
        if (hitEnemies.find(pTarget) != hitEnemies.end()) return;

        // EnemyBaseにキャスト
        BulletBase* pBullet = dynamic_cast<BulletBase*>(pTarget);

        // ダメージを与える
        DecreaseHp(pBullet->GetBulletParameter().damage_);

        // ヒットを記録
        hitEnemies.insert(pTarget);

        // 貫通しない場合は弾丸を消す
        if (pBullet->GetBulletParameter().isPenetration_ == 0) pBullet->KillMe();
    }

    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        transform_.position_ = currentPosition_;
    }
}

void Enemy_Fly::Attack()
{
}
