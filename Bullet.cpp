#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet.h"


//コンストラクタ
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), hModel_(-1), BulletKill_(0)
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Entity/Bullet.fbx");
    assert(hModel_ >= 0);
    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.1f);
    AddCollider(collision);
}

//更新
void Bullet::Update()
{
    //弾を飛ばす方向にベクトルを変換
    transform_.position_.x += move_.x;
    transform_.position_.y += move_.y;
    transform_.position_.z += move_.z;

    //弾を消す
    BulletKill_++;
    if (BulletKill_ >= 240)
    {
        KillMe();
    }
}

//描画
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet::Release()
{
}

void Bullet::OnCollision(GameObject* pTarget)
{
    // 名前にエネミーが含まれるオブジェクトに衝突したとき
    if (pTarget->GetObjectName().find("Enemy") != std::string::npos)
    {
        pTarget->KillMe();
    }
}