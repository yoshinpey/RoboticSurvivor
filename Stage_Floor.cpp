#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "Stage_Floor.h"
#include "StageManager.h"

#include "PlayScene.h"

namespace
{
    XMFLOAT3 collisionPosition = { 0.0f, -0.5f, 0.0f };     // 当たり判定の位置
    XMFLOAT3 collisionScale = { 100.0f, 1.0f, 100.0f };     // 当たり判定の大きさ
    std::string modelName = "Stage/Ground.fbx";             // モデル名
}

Stage_Floor::Stage_Floor(GameObject* parent)
    :StageBase(parent, StageType::FLOOR, "Stage_Floor"), hModel_(-1)
{
}

Stage_Floor::~Stage_Floor()
{
    // ステージリストから削除する
    PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
    pPlayScene->GetStageManager()->RemoveCompletedStages(this);
}

void Stage_Floor::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    // コライダー付与
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