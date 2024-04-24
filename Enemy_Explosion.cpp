#include "Enemy_Explosion.h"
#include "Engine/SphereCollider.h"
#include "BulletBase.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 1.0f, 0.0f };        // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 0.0f, 0.0f };          // モデルの回転
    struct AnimFrame
    {
        float startFrame = 0.0f;
        float endFrame = 100.0f;
        float speed = 0.75f;
    };
    AnimFrame anim;
}

Enemy_Explosion::Enemy_Explosion(GameObject* parent)
    : EnemyBase(parent, EnemyType::EXPLOSION, "Enemy_Explosion"), hModel_(-1), isFirstHit_(true), firstPosition_{0,0,0}, currentHp_(0)
{
    // INIファイルからデータを構造体へ流し込む
    status_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Explosion", "walkSpeed", 0, "Settings/EnemySettings.ini");
    status_.attackPower_                = GetPrivateProfileInt("Enemy_Explosion", "attackPower", 0, "Settings/EnemySettings.ini");
    status_.attackCooldown_             = GetPrivateProfileInt("Enemy_Explosion", "attackCooldown", 0, "Settings/EnemySettings.ini");
    status_.maxHp_                      = GetPrivateProfileFloat("Enemy_Explosion", "maxHp", 0, "Settings/EnemySettings.ini");
    status_.collisionScale_             = GetPrivateProfileFloat("Enemy_Explosion", "collisionScale", 0, "Settings/EnemySettings.ini");

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
    hModel_ = Model::Load("Enemy/Enemy_Explosion.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, anim.startFrame, anim.endFrame, anim.speed);

    // 当たり判定付与
    SphereCollider* pCollision = new SphereCollider(collisionOffset, status_.collisionScale_);
    AddCollider(pCollision);

    // モデルの回転
    transform_.rotate_.y = modelRotate.y;

    // 現在のHPを最大値で初期化
    currentHp_ = status_.maxHp_;    
}

void Enemy_Explosion::Update()
{
    /////////////これ本来はマネージャー通さないといけない
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
        // EnemyBaseにキャスト
        BulletBase* pBullet = dynamic_cast<BulletBase*>(pTarget);

        // 貫通しない場合はダメージを与えたら弾丸を消す
        if (pBullet->GetBulletParameter().isPenetration_ == 0)
        {
            DecreaseHp(pBullet->GetBulletParameter().damage_);
            pBullet->KillMe();
        }
        else
        {
            // 貫通するときの処理
            // 初回ヒットの場合
            if (isFirstHit_)
            {
                // ダメージを与える
                DecreaseHp(pBullet->GetBulletParameter().damage_);

                // 初回ヒットフラグをfalseにする
                isFirstHit_ = false;

                // 初回ヒット位置を記録
                firstPosition_ = pTarget->GetPosition();
            }
            else
            {
                // 初回ヒット座標と現在地の差分比較を行う
                XMFLOAT3 currentPosition = pTarget->GetPosition();
                float distance = CalculateDistance(firstPosition_, currentPosition);

                // 敵一体(当たり判定の直径)分貫通した場合、初回ヒットフラグを立て直す
                if (distance >= status_.collisionScale_*2)
                {
                    isFirstHit_ = true;
                }
            }
        }
    }
};


void Enemy_Explosion::Attack()
{
}

void Enemy_Explosion::IncreaseHp(float amount)
{
    currentHp_ += amount;
    if (currentHp_ > status_.maxHp_) {
        currentHp_ = status_.maxHp_;
    }
}

void Enemy_Explosion::DecreaseHp(float amount)
{
    currentHp_ -= amount;
    if (currentHp_ < 0) {
        currentHp_ = 0;
    }
}