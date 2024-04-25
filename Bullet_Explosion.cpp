#include "Engine/SphereCollider.h"
#include "Engine/Audio.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"
#include "JsonReader.h"
#include "Gun.h"


namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };    // 当たり判定の位置
    XMFLOAT3 modelScale = { 0.2f, 0.2f, 0.2f };         // モデルのサイズ
    XMFLOAT3 modelRotate = { 0.0f, 180.0f, 0.0f };      // モデルの回転
    std::vector<std::string> fileName = 
    {
        "Entity/Missile.fbx",
        "Sounds/Explode.wav"
    };
    //////////////////////////////
    const float velocity = 0.5f; // 上向き最大速度
    const float delta = 0.01f; // 
}

//コンストラクタ
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::EXPLOSION, "Bullet_Explosion"), hModel_(-1), hSound_(-1), pGun_(nullptr), IsBulletHit(false), isFirstHit(true)
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
    hSound_ = Audio::Load(fileName[1], false, 3);
    assert(hSound_ >= 0);

    transform_.scale_ = modelScale;
    transform_.rotate_.y = modelRotate.y;
    ////////////////////////
    // 初期速度を設定（上向き最大速度から開始）
    move_.y = velocity;

    //当たり判定
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);

    pGun_ = static_cast<Gun*>(FindObject("Gun"));
}

//更新
void Bullet_Explosion::Update()
{
    ///////////////////////
    // 上向き最大速度から徐々に下向きの力へ変化
    if (move_.y > -0.1)move_.y -= delta;

    //弾を飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    // 向きを合わせる
    XMFLOAT3 targetVector= pGun_->GetMoveDirection();
    RotateToTarget(targetVector);

    // 爆発する
    if (parameter_.killTimer_ <= 30)
    { 
        if (isFirstHit)
        {
            Audio::Play(hSound_, 0.2f);
            isFirstHit = false;
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
        isFirstHit = true;
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