#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

#include "Bullet.h"


//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), hModel_(-1), BulletKill_(0)
{
}

//�f�X�g���N�^
Bullet::~Bullet()
{
}

//������
void Bullet::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Entity/Bullet.fbx");
    assert(hModel_ >= 0);
    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.1f);
    AddCollider(collision);
}

//�X�V
void Bullet::Update()
{
    //�e���΂������Ƀx�N�g����ϊ�
    transform_.position_.x += move_.x;
    transform_.position_.y += move_.y;
    transform_.position_.z += move_.z;

    //�e������
    BulletKill_++;
    if (BulletKill_ >= 240)
    {
        KillMe();
    }
}

//�`��
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Bullet::Release()
{
}