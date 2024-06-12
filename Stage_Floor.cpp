#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "Stage_Floor.h"
#include "StageManager.h"

#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, -0.5f, 0.0f };     // �����蔻��̈ʒu
    XMFLOAT3 collisionScale = { 100.0f, 1.0f, 100.0f };     // �����蔻��̑傫��
    std::string modelName = "Stage/Ground.fbx";             // ���f����
}

Stage_Floor::Stage_Floor(GameObject* parent)
    :StageBase(parent, StageType::FLOOR, "Stage_Floor"), hModel_(-1)
{
}

Stage_Floor::~Stage_Floor()
{
    // �X�e�[�W���X�g����폜����
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetStageManager()->RemoveCompletedStages(this);
}

void Stage_Floor::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    // �R���C�_�[�t�^
    BoxCollider* pBoxCollider = new BoxCollider(collisionPosition, collisionScale);
    AddCollider(pBoxCollider);
}

void Stage_Floor::Update()
{
}

void Stage_Floor::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Stage_Floor::Release()
{
}