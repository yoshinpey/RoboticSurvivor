#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Enemy_Ground.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 1.0f, 0.0f };      // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // モデルの回転

    // モデルのアニメーション
    struct AnimFrame
    {
        int startFrame = 70;
        int endFrame = 260;
        float speed = 0.75f;
    }anim;
}

Enemy_Ground::Enemy_Ground(GameObject* parent)
    : EnemyBase(parent, EnemyType::GROUND, "Enemy_Ground"), 
    hModel_(-1), directionToPlayer_(0.0f, 0.0f, 0.0f), distanceToPlayer_(0.0f)
{
    // INIファイルからデータを構造体へ流し込む
    commonParameter_.walkSpeed_                  = GetPrivateProfileFloat("Enemy_Ground", "walkSpeed", 0, "Settings/EnemySettings.ini");
    commonStatus_.maxHp_ = GetPrivateProfileFloat("Enemy_Ground", "maxHp", 0, "Settings/EnemySettings.ini");
    commonStatus_.currentHp_ = commonStatus_.maxHp_;        // 現在のHPを最大値で初期化

    enemyStatus_.attackPower_                = GetPrivateProfileInt("Enemy_Ground", "attackPower", 0, "Settings/EnemySettings.ini");
    enemyStatus_.attackCooldown_             = GetPrivateProfileInt("Enemy_Ground", "attackCooldown", 0, "Settings/EnemySettings.ini");
    enemyStatus_.collisionScale_             = GetPrivateProfileFloat("Enemy_Ground", "collisionScale", 0, "Settings/EnemySettings.ini");

    enemyAlgorithm_.detectPlayerDistance_    = GetPrivateProfileInt("Enemy_Ground", "detectPlayerDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.patrolRadius_            = GetPrivateProfileInt("Enemy_Ground", "patrolRadius", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.approachDistance_        = GetPrivateProfileInt("Enemy_Ground", "approachDistance", 0, "Settings/EnemySettings.ini");
    enemyAlgorithm_.attackDistance_          = GetPrivateProfileInt("Enemy_Ground", "attackDistance", 0, "Settings/EnemySettings.ini");
}

Enemy_Ground::~Enemy_Ground()
{
    // 死んだエネミーをエネミーマネージャーのリストから削除する
    static_cast<PlayScene*>(FindObject("PlayScene"))->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Ground::Initialize()
{
    // モデルデータのロード
    hModel_ = Model::Load("Model/Enemy_Ground.fbx");
    assert(hModel_ >= 0);

    //アニメーション
    Model::SetAnimFrame(hModel_, anim.startFrame, anim.endFrame, anim.speed);

    // 当たり判定付与
    AddCollider(new SphereCollider(collisionOffset, enemyStatus_.collisionScale_));

    transform_.rotate_.y = modelRotate.y;
    transform_.position_.y = 0;
}

void Enemy_Ground::Update()
{
    /////////////////////// 今のところコイツは地上にだけ出す予定
    if (transform_.position_.y != 0)transform_.position_.y = 0;

    // 経過フレームを進める
    EnemyBase::Update();

    // 一定期間(フレーム)ごとに処理を行う
    if (IsEveryNFrames(30))
    {
        // プレイヤーへの方向ベクトル(正規化済)
        directionToPlayer_ = CheckPlayerDirection();

        // プレイヤーへの距離
        distanceToPlayer_ = CheckPlayerDistance();
    }

    // 許可された距離までプレイヤーに接近
    if (enemyAlgorithm_.attackDistance_ <= distanceToPlayer_)
    {
        ApproachPlayer(directionToPlayer_);
    }

    // プレイヤーの方向を向くように視界を回転
    RotateTowardsPlayer(directionToPlayer_);
}

void Enemy_Ground::Draw()
{
    // ダメージシェーダーの適応処理（前処理）
    PreDrawDamageShader();

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // ダメージシェーダーの適応処理（後処理）
    PostDrawDamageShader();
}

void Enemy_Ground::Release()
{
}

void Enemy_Ground::OnCollision(GameObject* pTarget)
{       
    // 銃弾に当たったとき
    if (pTarget->GetObjectName().find("Bullet") != std::string::npos)
    {
        // 銃で撃たれたリアクション
        BulletHit();
    }

    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        // エネミーベースの関数でエネミー同士の判定
        CollisionDetectionWithEnemy(static_cast<EnemyBase*>(pTarget));
    }
}

void Enemy_Ground::Attack()
{
    // ぶつかり攻撃のみ行うため未定義
}
