#include "Engine/Model.h"

#include "Enemy_Ground.h"


//コンストラクタ
Enemy_Ground::Enemy_Ground(GameObject* parent)
    :GameObject(parent, "Enemy_Ground"), hModel_(-1)
{
}

//デストラクタ
Enemy_Ground::~Enemy_Ground()
{
}

//初期化
void Enemy_Ground::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("ファイル名");
    assert(hModel_ >= 0);
}

//更新
void Enemy_Ground::Update()
{
}

//描画
void Enemy_Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Enemy_Ground::Release()
{
}