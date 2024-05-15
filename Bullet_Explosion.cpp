#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"
#include "JsonReader.h"
#include "Gun.h"
#include "AudioManager.h"
#include "EffectManager.h"

namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };    // 当たり判定の位置
    XMFLOAT3 modelScale = { 0.2f, 0.2f, 0.2f };         // モデルのサイズ
    std::string modelName = "Entity/Missile.fbx";       // モデル名

    //////////////////////////////
    const float gravity = -0.0025f;          // 重力
    const float accelerationLimit = -0.3f;  // 加速限界
}

//コンストラクタ
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::EXPLOSION, "Bullet_Explosion"), hModel_(-1), pGun_(nullptr), 
    isFirstHit_(true), gravity_(gravity), verticalSpeed_(0.0f)
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
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    transform_.scale_ = modelScale;

    //当たり判定
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);

    pGun_ = static_cast<Gun*>(FindObject("Gun"));
}

//更新
void Bullet_Explosion::Update()
{
    // 加速度制限
    if(verticalSpeed_ >= accelerationLimit) verticalSpeed_ += gravity_;
    
    // 位置を保存する
    XMFLOAT3 prePos = transform_.position_;

    // 重力を加算して放物線運動させる
    transform_.position_.y += verticalSpeed_;

    // 銃クラスであらかじめ計算していた方向(銃口の先)へ飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // モデルの向きを合わせる
    XMFLOAT3 targetVector = CalculateFloat3Sub(transform_.position_, prePos);
    RotateToTarget(targetVector);

    // 爆発する
    if (parameter_.killTimer_ <= 0)
    { 
        AudioManager::Play(AudioManager::AUDIO_ID::EXPLODE);
        EffectManager::CreateVfx(transform_.position_, VFX_TYPE::EXPLODE);
        pCollision_->SetRadius(parameter_.collisionScale_*20.0f);
        KillMe(); 
    }

    //弾を消す
    parameter_.killTimer_--;
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
void Bullet_Explosion::RotateToTarget(XMFLOAT3& targetVector)
{
    targetVector = NormalizeFloat3(targetVector);

    XMFLOAT3 rot = XMFLOAT3();
    rot.x = XMConvertToDegrees(asinf(targetVector.y));
    rot.y = XMConvertToDegrees(atan2f(targetVector.x, targetVector.z)) + 180.0f;
    transform_.rotate_ = rot;
}


void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // 地面関連の物体に当たったとき
    if (pTarget->GetObjectName().find("Stage") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
    // 敵に当たったとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        parameter_.killTimer_ = 0;
    }
};