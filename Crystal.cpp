#include "Engine/Model.h"

#include "Crystal.h"


//コンストラクタ
Crystal::Crystal(GameObject* parent)
    :GameObject(parent, "Crystal"), hModel_(-1)
{
}

//デストラクタ
Crystal::~Crystal()
{
}

//初期化
void Crystal::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("ファイル名");
    assert(hModel_ >= 0);
}

//更新
void Crystal::Update()
{
}

//描画
void Crystal::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Crystal::Release()
{
}