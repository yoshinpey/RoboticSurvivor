#include "Engine/Model.h"

#include "Bomb.h"


//コンストラクタ
Bomb::Bomb(GameObject* parent)
    :GameObject(parent, "Bomb"), hModel_(-1)
{
}

//デストラクタ
Bomb::~Bomb()
{
}

//初期化
void Bomb::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("ファイル名");
    assert(hModel_ >= 0);
}

//更新
void Bomb::Update()
{
}

//描画
void Bomb::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bomb::Release()
{
}