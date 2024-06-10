#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "Stage.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, -0.5f, 0.0f };    // �����蔻��̈ʒu
    XMFLOAT3 collisionScale = { 100.0f, 1.0f, 100.0f };      // �����蔻��̑傫��
    std::string modelName = "Stage/Ground.fbx";     // ���f����
}

Stage::Stage(GameObject* parent)
    :StageBase(parent, StageType::GROUND, "Stage_a"), hModel_(-1)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    // �R���C�_�[�t�^
    BoxCollider* pBoxCollider = new BoxCollider(collisionPosition, collisionScale);
    AddCollider(pBoxCollider);
}

void Stage::Update()
{
}

void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Stage::Release()
{
}