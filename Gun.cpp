#include "Engine/Model.h"
#include "Engine/Input.h"

#include "InputManager.h"
#include "Gun.h"
#include "Bullet_Normal.h"

namespace
{
    XMFLOAT3 offset = {0.25f, -1.25f, 1.50f };
}

Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), Bullet_speed(1), AttackCool_(0), Cool_(0)
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
    // 銃モデル先端
    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");

    // 銃モデル根本
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");

    // 速度と向きを設定
    XMFLOAT3 move = CalculateBulletMove(GunTop, GunRoot);

    //発砲
    if (InputManager::IsShoot())
    {
        // 弾を生成
        Bullet_Normal* pBullet_Normal = Instantiate<Bullet_Normal>(GetParent()->GetParent()->GetParent());
        pBullet_Normal->SetPosition(GunTop);
        pBullet_Normal->SetMove(move);
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

XMFLOAT3 Gun::CalculateBulletMove(XMFLOAT3 top, XMFLOAT3 root)
{
    // 射出方向計算(top - root)
    XMVECTOR vMove = XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root));
    // 正規化
    vMove = XMVector3Normalize(vMove);
    // 弾速を設定
    vMove *= Bullet_speed;
    // float3型に戻す
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}