#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Explosion.h"


//コンストラクタ
Bullet_Explosion::Bullet_Explosion(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Explosion"), hModel_(-1)
{
    parameter_.damage_          = GetPrivateProfileFloat("Bullet_Explosion", "damage", 0, "Settings/WeaponSettings.ini");
    parameter_.shotCoolTime_    = GetPrivateProfileFloat("Bullet_Explosion", "shotCoolTime", 0, "Settings/WeaponSettings.ini");
    parameter_.speed_           = GetPrivateProfileFloat("Bullet_Explosion", "speed", 0, "Settings/WeaponSettings.ini");
    parameter_.killTimer_       = GetPrivateProfileFloat("Bullet_Explosion", "killTimer", 0, "Settings/WeaponSettings.ini");
    parameter_.collisionScale_  = GetPrivateProfileFloat("Bullet_Explosion", "collisionScale", 0, "Settings/WeaponSettings.ini");
    parameter_.isPenetration_   = GetPrivateProfileInt("Bullet_Explosion", "isPenetration", 0, "Settings/WeaponSettings.ini");
}

//デストラクタ
Bullet_Explosion::~Bullet_Explosion()
{
}

//初期化
void Bullet_Explosion::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Entity/Bullet.fbx");
    assert(hModel_ >= 0);

    //当たり判定
    collision_ = new SphereCollider(XMFLOAT3(0, 0, 0), parameter_.collisionScale_);
    AddCollider(collision_);
}

//更新
void Bullet_Explosion::Update()
{
    //弾を飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, move_);

    //弾を消す
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) { KillMe(); }
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
        pTarget->KillMe();

        // 貫通しない場合は自身も消す
        if (parameter_.isPenetration_ == 0) KillMe();
    }
}