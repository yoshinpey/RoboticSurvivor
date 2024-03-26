#include "Engine/SphereCollider.h"
#include "Engine/Audio.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"
#include "JsonReader.h"


namespace
{
    XMFLOAT3 collisionOffset = { 0.0f, 0.0f, 0.0f };      // 当たり判定の位置
}

//コンストラクタ
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Explosion"), hModel_(-1), hSound_(-1)
{
    // JSONファイル読み込み
    JsonReader::Load("Settings/JsonWeaponSettings.json");
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
    hModel_ = Model::Load("Entity/Missile.fbx");
    assert(hModel_ >= 0);

    //当たり判定
    pCollision_ = new SphereCollider(collisionOffset, parameter_.collisionScale_);
    AddCollider(pCollision_);

    transform_.scale_ = { 0.2f, 0.2f, 0.2f };
    transform_.rotate_.y = 180.0f;

    //hSound_ = Audio::Load("Sounds/Explosion.wav", false, 1);
    //assert(hSound_ >= 0);
}

//更新
void Bullet_Explosion::Update()
{
    //弾を飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);
   
    static bool isFirst = true;
    // 爆発する
    if (parameter_.killTimer_ <= 30)
    { 
        //if (isFirst)
        //{
        //    Audio::Play(hSound_);
        //    isFirst = false;
        //}
        transform_.scale_.x *= 1.1;
        transform_.scale_.y *= 1.1;
        transform_.scale_.z *= 1.1;
        pCollision_->SetRadius(transform_.scale_.x);
    }

    //弾を消す
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) 
    { 
        isFirst = true;
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

void Bullet_Explosion::OnCollision(GameObject* pTarget)
{
    // 名前にエネミーが含まれるオブジェクトに衝突したとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {

        // 貫通しない場合は自身を消す
        if (parameter_.isPenetration_ == 0) KillMe();
    }
}