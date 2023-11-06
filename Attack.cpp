#include "Engine/Model.h"

#include "Attack.h"

//コンストラクタ
Attack::Attack(GameObject* parent)
    :GameObject(parent, "Attack"), hModel_(-1)
{
}

//デストラクタ
Attack::~Attack()
{
}

//初期化
void Attack::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("ファイル名");
    assert(hModel_ >= 0);
}

//更新
void Attack::Update()
{
}

//描画
void Attack::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Attack::Release()
{
}