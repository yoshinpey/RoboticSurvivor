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
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Entity/Rifle_re.fbx");
    assert(hModel_ >= 0);

    //�v���C���[�̎�̈ʒu�܂Œ���
    transform_.position_ = offset;
}

void Gun::Update()
{
    // �e���f����[
    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");

    // �e���f�����{
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");

    // ���x�ƌ�����ݒ�
    XMFLOAT3 move = CalculateBulletMove(GunTop, GunRoot);

    //���C
    if (InputManager::IsShoot())
    {
        // �e�𐶐�
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