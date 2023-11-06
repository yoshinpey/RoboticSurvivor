#include "Engine/Model.h"

#include "Attack.h"

//�R���X�g���N�^
Attack::Attack(GameObject* parent)
    :GameObject(parent, "Attack"), hModel_(-1)
{
}

//�f�X�g���N�^
Attack::~Attack()
{
}

//������
void Attack::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);
}

//�X�V
void Attack::Update()
{
}

//�`��
void Attack::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Attack::Release()
{
}