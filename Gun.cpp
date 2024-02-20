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
    //���C
    if (!InputManager::IsShoot()) return;

    float bulletSpeed = 1.0f;
    // �e�𐶐�
    // PlayScene<-Player<-Aim<-Gun(������)
    BulletBase* pNewBullet = nullptr;

    // �����ɂ���ăo���b�g�^�C�v�����肷��
    if (false)
    {
        pNewBullet = Instantiate<Bullet_Normal>(GetParent()->GetParent()->GetParent());
        bulletSpeed = 1.0f;
    }
    else
    {
        pNewBullet = Instantiate<Bullet_Explosion>(GetParent()->GetParent()->GetParent());
        bulletSpeed = 0.5f;
    }

    // �e���f����[
    XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    // �e���f�����{
    XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
    // ���x�ƌ�����ݒ�
    XMFLOAT3 move = CalculateBulletMovement(GunTop, GunRoot, bulletSpeed);

    pNewBullet->SetPosition(GunTop);
    pNewBullet->SetMove(move);
    pNewBullet->SetAddSpeed(1.0f);

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
    // �ˏo�����v�Z(top - root)
    XMVECTOR vMove = XMVectorSubtract(XMLoadFloat3(&top), XMLoadFloat3(&root));
    // ���K��
    vMove = XMVector3Normalize(vMove);
    // �e����ݒ�
    vMove *= bulletSpeed;
    // float3�^�ɖ߂�
    XMFLOAT3 move;
    XMStoreFloat3(&move, vMove);
    return move;
}