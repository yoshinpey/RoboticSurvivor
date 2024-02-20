#include "Engine/Model.h"
#include "Engine/Input.h"

#include "BulletManager.h"
#include "InputManager.h"
#include "Gun.h"
#include "Bullet_Normal.h"

namespace {
    XMFLOAT3 offset = { -1.25f, 0.25f, 1.5f };
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
    transform_.position_.y = offset.y;
    transform_.position_.x = offset.x;
    transform_.position_.z = offset.z;

}

void Gun::Update()
{
    // 銃モデル先端
    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    GunTop = { GunTop.x - offset.x, GunTop.y - offset.y, GunTop.z - offset.z };

    // 銃モデル根本
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
    GunRoot = { GunRoot.x - offset.x, GunRoot.y - offset.y, GunRoot.z - offset.z };

    // 速度と向きを設定
    XMFLOAT3 move = CalculateBulletMove(GunTop, GunRoot);

    //発砲
    if (InputManager::IsShoot())
    {
        // 弾を生成
        Bullet_Normal* b = Instantiate<Bullet_Normal>(GetParent()->GetParent());
        b->SetPosition(GunTop);
        b->SetMove(move);
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