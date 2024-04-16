
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "InputManager.h"
#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"
#include "Engine/Audio.h"

namespace
{
    XMFLOAT3 handOffset = { 0.6f, -1.25f, 1.50f };       // 移動量
    XMFLOAT3 modelScale = { 1.0f, 1.0f, 1.0f };         // モデルサイズ
    std::string modelName = "Entity/Rifle.fbx";         // モデル名
    std::string soundName = "Sounds/Shot.wav";          // サウンド名
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), normalShotCool_(0), explosionShotCool_(0), hSound_(-1)
{
}

Gun::~Gun()
{
}

void Gun::Initialize()
{
    // データのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    hSound_ = Audio::Load(soundName, false, 3);
    assert(hSound_ >= 0);

    //プレイヤーの手の位置まで調整
    transform_.position_ = handOffset;
    transform_.scale_ = modelScale;
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
        Audio::Play(hSound_,0.2);
        ShootBullet<Bullet_Normal>();
        normalShotCool_ = shotCoolTime_;
    }
    else
    {
        Audio::Stop(hSound_);
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
    // 銃は常に手前に表示したいので深度を無視する
    Direct3D::SetDepthBafferWriteEnable(false);

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // 深度設定を戻す
    Direct3D::SetDepthBafferWriteEnable(true);
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