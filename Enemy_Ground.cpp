#include "Engine/Model.h"

#include "Enemy_Ground.h"


//�R���X�g���N�^
Enemy_Ground::Enemy_Ground(GameObject* parent)
    :GameObject(parent, "Enemy_Ground"), hModel_(-1)
{
}

//�f�X�g���N�^
Enemy_Ground::~Enemy_Ground()
{
}

//������
void Enemy_Ground::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);
}

//�X�V
void Enemy_Ground::Update()
{
}

//�`��
void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Enemy_Ground::Release()
{
}