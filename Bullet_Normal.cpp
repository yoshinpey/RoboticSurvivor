#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet_Normal.h"


//コンストラクタ
Bullet_Normal::Bullet_Normal(GameObject* parent)
    :BulletBase(parent, BulletType::NORMAL, "Bullet_Normal"), hModel_(-1)
{
    parameter_.damage_          = GetPrivateProfileFloat("Bullet_Normal", "damage", 0, "Settings/WeaponSettings.ini");
    parameter_.shotCoolTime_    = GetPrivateProfileFloat("Bullet_Normal", "shotCoolTime", 0, "Settings/WeaponSettings.ini");
    parameter_.speed_           = GetPrivateProfileFloat("Bullet_Normal", "speed", 0, "Settings/WeaponSettings.ini");
    parameter_.killTimer_       = GetPrivateProfileFloat("Bullet_Normal", "killTimer", 0, "Settings/WeaponSettings.ini");
}

//デストラクタ
Bullet_Normal::~Bullet_Normal()
{
}

//初期化
void Bullet_Normal::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Entity/Bullet.fbx");
    assert(hModel_ >= 0);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.1f);
    AddCollider(collision);
}

//更新
void Bullet_Normal::Update()
{
    //弾を飛ばす
    transform_.position_ = CalculateFloat3Add(transform_.position_, GetMove());

    //弾を消す
    parameter_.killTimer_--;
    if (parameter_.killTimer_ <= 0) { KillMe(); }
}

//描画
void Bullet_Normal::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet_Normal::Release()
{
}

void Bullet_Normal::OnCollision(GameObject* pTarget)
{
    // 名前にエネミーが含まれるオブジェクトに衝突したとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        pTarget->KillMe();
    }
}