#include "Engine/Model.h"

#include "Crystal.h"


//�R���X�g���N�^
Crystal::Crystal(GameObject* parent)
    :GameObject(parent, "Crystal"), hModel_(-1)
{
}

//�f�X�g���N�^
Crystal::~Crystal()
{
}

//������
void Crystal::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);
}

//�X�V
void Crystal::Update()
{
}

//�`��
void Crystal::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Crystal::Release()
{
}