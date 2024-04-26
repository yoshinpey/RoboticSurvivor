#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "Ground.h"

namespace
{
    std::string modelName = "Stage/Ground.fbx";     // モデル名
}

//コンストラクタ
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{
}

//デストラクタ
Ground::~Ground()
{
}

//初期化
void Ground::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(modelName);
    assert(hModel_ >= 0);

    // コライダー付与
    BoxCollider* pBoxCollider = new BoxCollider(XMFLOAT3{0,0,0}, XMFLOAT3 {80.0f, 0.2f, 80.0f});
    AddCollider(pBoxCollider);
}

//更新
void Ground::Update()
{
}

//描画
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ground::Release()
{
}