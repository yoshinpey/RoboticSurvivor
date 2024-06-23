#include "Engine/Model.h"

#include "AudioManager.h"
#include "InputManager.h"

#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"


namespace
{
    const XMFLOAT3 handOffset = { 0.6f, -1.25f, 1.50f };      // 移動量
    const XMFLOAT3 modelScale = { 1.0f, 1.0f, 1.0f };         // モデルサイズ
    const std::string modelName = "Entity/Rifle.fbx";         // モデル名
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), moveDirection_{ 0,0,0 }
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

    //プレイヤーの手の位置まで調整
    transform_.position_ = handOffset;
    transform_.scale_ = modelScale;

    // バレットタイプのenumサイズで初期化
    bulletInfoList_.resize(static_cast<int>(BulletType::MAX));
}

void Gun::Update()
{
    // クールタイムを減らす
    for (auto& bullet : bulletInfoList_) { bullet.coolTime_--; }

    // 通常射撃
    if (InputManager::IsShoot() && bulletInfoList_[(int)BulletType::NORMAL].coolTime_ <= 0)
    {
        AudioManager::Play(AudioManager::AUDIO_ID::SHOT, 0.1f);
        ShootBullet<Bullet_Normal>(BulletType::NORMAL);
    }
    else
    {
        AudioManager::Stop(AudioManager::AUDIO_ID::SHOT);
    }

    // 特殊射撃
    if (InputManager::IsWeaponAction() && bulletInfoList_[(int)BulletType::EXPLOSION].coolTime_ <= 0)
    {
        ShootBullet<Bullet_Explosion>(BulletType::EXPLOSION);
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
    // 射出方向を計算して正規化し速度を掛ける  (top - root) * speed
    XMVECTOR vMove = XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root))) * bulletSpeed;

    // XMFLOAT3型に戻す
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}

template <class T>
void Gun::ShootBullet(BulletType type)
{
    // これは高頻度で処理するので、わかりにくいけどFindではなく親をたどって生成（Aim->Player->PlayScene）
    BulletBase* pNewBullet = Instantiate<T>(GetParent()->GetParent()->GetParent());

    // パラメータ設定
    float bulletSpeed = pNewBullet->GetBulletParameter().speed_;
    bulletInfoList_[(int)type].coolTime_ = pNewBullet->GetBulletParameter().shotCoolTime_;

    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");

    // モデルのボーン位置を元に、射出方向･速度計算する
    moveDirection_ = CalculateBulletMovement(GunTop, GunRoot, bulletSpeed);

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(moveDirection_);
}