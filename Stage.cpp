#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "Stage.h"

namespace
{
    std::string modelName = "Stage/Ground.fbx";     // ���f����
}

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage_a"), hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    // �R���C�_�[�t�^
    BoxCollider* pBoxCollider = new BoxCollider(XMFLOAT3{0,0,0}, XMFLOAT3 {80.0f, 0.2f, 80.0f});
    AddCollider(pBoxCollider);
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}