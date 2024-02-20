#include "Engine/Model.h"
#include "Engine/Input.h"

#include "InputManager.h"
#include "Gun.h"
#include "Bullet_Normal.h"
#include "Bullet_Explosion.h"

namespace
{
    XMFLOAT3 offset = {0.25f, -1.25f, 1.50f };
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), bulletSpeed_(0.0f), AttackCool_(0), Cool_(0)
{
}

Gun::~Gun()
{
}

void Gun::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Entity/Rifle_re.fbx");
    assert(hModel_ >= 0);

    //プレイヤーの手の位置まで調整
    transform_.position_ = offset;
}

void Gun::Update()
{
    if (!InputManager::IsShoot())return;

    // 弾を生成
    // 親:PlayScene<-Player<-Aim<-Gun(今ここ)
    BulletBase* pNewBullet = nullptr;
    //発砲
    if (InputManager::IsWalk())
    {
        pNewBullet = Instantiate<Bullet_Normal>(GetParent()->GetParent()->GetParent());
        bulletSpeed_ = pNewBullet->GetBulletParameter_().speed_;
    }
    else
    {
        pNewBullet = Instantiate<Bullet_Explosion>(GetParent()->GetParent()->GetParent());
        bulletSpeed_ = pNewBullet->GetBulletParameter_().speed_;
    }

    // 銃モデル先端
    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    // 銃モデル根本
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
    // 速度と向きを設定
    XMFLOAT3 move = CalculateBulletMovement(GunTop, GunRoot, bulletSpeed_);
    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(move);
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

    // 弾速を追加設定
    vMove *= bulletSpeed;

    // float3型に戻す
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}