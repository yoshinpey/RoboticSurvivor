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
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Entity/Rifle_re.fbx");
    assert(hModel_ >= 0);

    //�v���C���[�̎�̈ʒu�܂Œ���
    transform_.position_.y = offset.y;
    transform_.position_.x = offset.x;
    transform_.position_.z = offset.z;

}

void Gun::Update()
{
    // �e���f����[
    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    GunTop = { GunTop.x - offset.x, GunTop.y - offset.y, GunTop.z - offset.z };

    // �e���f�����{
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
    GunRoot = { GunRoot.x - offset.x, GunRoot.y - offset.y, GunRoot.z - offset.z };

    // ���x�ƌ�����ݒ�
    XMFLOAT3 move = CalculateBulletMove(GunTop, GunRoot);

    //���C
    if (InputManager::IsShoot())
    {
        // �e�𐶐�
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
    // �ˏo�����v�Z(top - root)
    XMVECTOR vMove = XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root));
    // ���K��
    vMove = XMVector3Normalize(vMove);
    // �e����ݒ�
    vMove *= Bullet_speed;
    // float3�^�ɖ߂�
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}