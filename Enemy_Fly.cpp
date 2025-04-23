#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Enemy_Fly.h"
#include "BulletBase.h"
#include "EnemyManager.h"
#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };      // 当たり判定の位置
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };          // モデルの回転
}

Enemy_Fly::Enemy_Fly(GameObject* parent)
    : EnemyBase(parent, EnemyType::FLY, "Enemy_Fly"), 
    hModel_(-1), directionToPlayer_(0.0f, 0.0f, 0.0f), distanceToPlayer_(0.0f)
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
    // 死んだエネミーをエネミーマネージャーのリストから削除する
    static_cast<PlayScene*>(FindObject("PlayScene"))->GetEnemyManager()->RemoveDeadEnemies(this);
}

void Enemy_Fly::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Model/Enemy_Fly.fbx");
    assert(hModel_ >= 0);

    // 当たり判定付与
    AddCollider(new SphereCollider(collisionOffset, enemyStatus_.collisionScale_));

    transform_.rotate_.y = modelRotate.y;

}

void Enemy_Fly::Update()
{
    // 経過フレームを進める
    EnemyBase::Update();

    // 一定期間(フレーム)ごとに処理を行う
    if (IsEveryNFrames(30))
    {
        // プレイヤーへの距離
        distanceToPlayer_ = CheckPlayerDistance();
    }

    // プレイヤーへの方向ベクトル(正規化済)
    directionToPlayer_ = CheckPlayerDirection();

    // 許可された距離までプレイヤーに接近
    if (enemyAlgorithm_.attackDistance_ <= distanceToPlayer_)
    {
        ApproachPlayer(directionToPlayer_);
        if (transform_.rotate_.x != 0.0f) transform_.rotate_.x = 0.0f;
    }
    else
    {
        Attack();
    }

    // プレイヤーの方向を向くように視界を回転
    RotateTowardsPlayer(directionToPlayer_);
    // 空を飛ぶからX軸考慮の回転
    // RotateTowardsPlayer3D(directionToPlayer_);
}

void Enemy_Fly::Draw()
{
    // ダメージシェーダーの適応処理（前処理）
    PreDrawDamageShader();

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // ダメージシェーダーの適応処理（後処理）
    PostDrawDamageShader();
}

void Enemy_Fly::Release()
{
}

void Enemy_Fly::OnCollision(GameObject* pTarget)
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

void Enemy_Fly::Attack()
{
    // 体を傾ける
    // XZ平面上での方向
    XMVECTOR toPlayerXZ = XMVector3Normalize(XMVectorSet(directionToPlayer_.x, 0, directionToPlayer_.z, 0));

    // X軸上下方向にどれだけ傾けるか
    float pitch = -atan2(directionToPlayer_.y, XMVectorGetX(XMVector3Length(toPlayerXZ))); // 高さと距離で角度計算
    transform_.rotate_.x = XMConvertToDegrees(pitch);

    //////これは前の処理
    // *アプローチ距離より遠ければ近づく
    // *攻撃範囲レンジ(アプローチ距離+5)を満たしている
    // *攻撃クールダウンが0になっている
    // *これらの条件を外れたらアニメーションやサウンドをストップ

    // プレイヤーへの方向を計算する
    // 攻撃チャージアニメーション、サウンドスタート(これはあとで追加。とりあえずコメントアウトしとく)
    // チャージ終了で弾を発射
}
