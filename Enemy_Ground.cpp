#include "Enemy_Ground.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, 1.0f, 0.0f };      // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // モデルの回転
}

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), hModel_(-1)
{
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    status_.maxHp_                      = GetPrivateProfileFloat("Enemy_Ground", "maxHp", 0, "Settings/EnemySettings.ini");
    status_.collisionScale_             = GetPrivateProfileFloat("Enemy_Ground", "collisionScale", 0, "Settings/EnemySettings.ini");
    // 現在のHPを最大値で初期化
    currentHp_ = status_.maxHp_;

    algorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Ground", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Ground", "patrolRadius", 0, "Settings/EnemySettings.ini");
    algorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Ground", "approachDistance", 0, "Settings/EnemySettings.ini");
    algorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Ground", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Ground::~Enemy_Ground()
{
    // エネミーのマネージャーリストから死んだエネミーを削除する
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Ground::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load("Enemy/Enemy_Ground.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    //Model::SetAnimFrame(hModel_, 0, 120, 0.75);
     
    // 当たり判定付与
    SphereCollider* pCollision = new SphereCollider(collisionPosition, status_.collisionScale_);
    AddCollider(pCollision);

    transform_.rotate_.y = modelRotate.y;

}

void Enemy_Ground::Update()
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
}

void Enemy_Ground::Attack()
{
}
