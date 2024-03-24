#include "Engine/Model.h"
#include "Engine/Input.h"

#include "InputManager.h"
#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"
#include "Engine/Audio.h"

namespace
{
    XMFLOAT3 handOffset = {0.6f, -1.25f, 1.50f };       // 移動量
    std::string modelName = "Entity/Rifle.fbx";         // モデル
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), normalShotCool_(0), explosionShotCool_(0)
{
}

Gun::~Gun()
{
}

void Gun::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    //プレイヤーの手の位置まで調整
    transform_.position_ = handOffset;
}

void Gun::Update()
{
    // 通常射撃のクールダウン減少
    if (normalShotCool_ > 0) normalShotCool_--;

    // 特殊射撃のクールダウン減少
    if (explosionShotCool_ > 0) explosionShotCool_--;

    // 通常射撃
    if (InputManager::IsShoot() && normalShotCool_ <= 0)
    {
        ShootBullet<Bullet_Normal>();
        normalShotCool_ = shotCoolTime_;
    }

    // 特殊射撃
    if (InputManager::IsWeaponAction() && explosionShotCool_ <= 0)
    {
        ShootBullet<Bullet_Explosion>();
        explosionShotCool_ = shotCoolTime_;
    }
}

void Gun::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Gun::Release()
{
}

XMFLOAT3 Gun::CalculateBulletMovement(XMFLOAT3 top, XMFLOAT3 root, float bulletSpeed)
{
    // 射出方向を計算して正規化  (top - root)
    XMVECTOR vMove = XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root)));

    // 弾速を追加設定(銃に種類が増えたとき用)
    vMove *= bulletSpeed;

    // float3型に戻す
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}

template <class T>
void Gun::ShootBullet()
{
    BulletBase* pNewBullet = Instantiate<T>(GetParent()->GetParent()->GetParent());
    float bulletSpeed = pNewBullet->GetBulletParameter().speed_;
    shotCoolTime_ = pNewBullet->GetBulletParameter().shotCoolTime_;

    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
    XMFLOAT3 move = CalculateBulletMovement(GunTop, GunRoot, bulletSpeed);

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(move);
}
