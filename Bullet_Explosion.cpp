#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"
#include "JsonReader.h"
#include "Gun.h"
#include "AudioManager.h"


namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };    // 当たり判定の位置
    XMFLOAT3 modelScale = { 0.2f, 0.2f, 0.2f };         // モデルのサイズ
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };      // モデルの回転
    std::vector<std::string> fileName = 
    {
        "Entity/Missile.fbx"
    };
    //////////////////////////////
    const float initialVelocity = 0.0f;     // 初速度
    const float gravity = -0.003f;          // 重力
    const float accelerationLimit = -0.2f;
}

//コンストラクタ
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::EXPLOSION, "Bullet_Explosion"), hModel_(-1), pGun_(nullptr), 
    isFirstHit_(true), gravity_(gravity), verticalSpeed_(initialVelocity)
{
    // JSONファイル読み込み
    JsonReader::Load("Settings/WeaponSettings.json");
    auto& bullet_explosion = JsonReader::GetSection("Bullet_Explosion");

    // パラメータを取得
    parameter_.damage_ = bullet_explosion["damage"];
    parameter_.shotCoolTime_ = bullet_explosion["shotCoolTime"];
    parameter_.speed_ = bullet_explosion["speed"];
    parameter_.killTimer_ = bullet_explosion["killTimer"];
    parameter_.collisionScale_ = bullet_explosion["collisionScale"];
    parameter_.isPenetration_ = bullet_explosion["isPenetration"];
}

//デストラクタ
Bullet_Explosion::~Bullet_Explosion()
{
}

//初期化
void Bullet_Explosion::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(fileName[0]);
    assert(hModel_ >= 0);

    transform_.scale_ = modelScale;
    transform_.rotate_.y = modelRotate.y;

    //当たり判定
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);

    pGun_ = static_cast<Gun*>(FindObject("Gun"));
}

//更新
void Bullet_Explosion::Update()
{
    ///////////////////////
    
    // 加速度制限
    if(verticalSpeed_ >= accelerationLimit) verticalSpeed_ += gravity_;

    // 放物線運動させる
    transform_.position_.y += verticalSpeed_;

    // 銃クラスであらかじめ計算していた方向へ飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // 向きを合わせる
    XMFLOAT3 targetVector= pGun_->GetMoveDirection();
    RotateToTarget(targetVector);

    // 爆発する
    if (parameter_.killTimer_ <= 30)
    { 
        // 初回被弾時の処理
        if (isFirstHit_)
        {
            AudioManager::Play(AudioManager::AUDIO_ID::EXPLODE);
            isFirstHit_ = false;
        }
        transform_.scale_.x *= 1.1f;
        transform_.scale_.y *= 1.1f;
        transform_.scale_.z *= 1.1f;
        pCollision_->SetRadius(transform_.scale_.x);
    }

    //弾を消す
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) 
    { 
        isFirstHit_ = true;
        KillMe(); 
    }
}

//描画
void Bullet_Explosion::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet_Explosion::Release()
{
}

// 弾の向きを対象方向へ回転させる
void Bullet_Explosion::RotateToTarget(const XMFLOAT3& targetVector)
{
    // 向かせたい方向
    XMVECTOR vTargetVector = -XMVector3Normalize(XMVectorSet(targetVector.x, 0, targetVector.z, 0));

    // 現在向いている方向
    float rotY = XMConvertToRadians(transform_.rotate_.y);
    XMVECTOR rotForward = XMVector3Normalize(XMVectorSet(sinf(rotY), 0, cosf(rotY), 0));

    // 内積と外積を計算
    float dot = XMVectorGetX(XMVector3Dot(rotForward, vTargetVector));
    XMVECTOR cross = XMVector3Cross(rotForward, vTargetVector);

    // 角度を計算して回転
    float angle = static_cast<float>(atan2(XMVectorGetY(cross), dot));
    transform_.rotate_.y += XMConvertToDegrees(angle);
}


void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // 地面関連の物体に当たったとき
    if (pTarget->GetObjectName().find("Ground") != std::string::npos)
    {
        parameter_.killTimer_ = 30;
        KillMe();
    }
};