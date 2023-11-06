#include "Engine/BoxCollider.h"
#include "Engine/Model.h"

#include "Ground.h"


//�R���X�g���N�^
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{
}

//�f�X�g���N�^
Ground::~Ground()
{
}

//������
void Ground::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Stage/Ground.fbx");
    assert(hModel_ >= 0);

    //�����蔻��
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, -4, 0), XMFLOAT3(5, 7, 5));
    AddCollider(collision);
}

//�X�V
void Ground::Update()
{
}

//�`��
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Ground::Release()
{
}

//�����蔻��
void Ground::OnCollision(GameObject* pTarget)
{
    //�e�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Bullet")
    {

    }

    //�G�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Enemy")
    {

    }

    //�v���C���[�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Player")
    {

    }

}
