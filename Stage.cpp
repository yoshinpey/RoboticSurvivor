#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "Stage.h"

namespace
{
    std::string modelName = "Stage/Ground.fbx";     // モデル名
}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage_a"), hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    // コライダー付与
    BoxCollider* pBoxCollider = new BoxCollider(XMFLOAT3{0,0,0}, XMFLOAT3 {80.0f, 0.2f, 80.0f});
    AddCollider(pBoxCollider);
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}