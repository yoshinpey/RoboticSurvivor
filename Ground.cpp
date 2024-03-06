#include "Engine/Model.h"

#include "Ground.h"

namespace
{
    std::string modelName = "Stage/Ground.fbx";     // ���f����
}

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
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);
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