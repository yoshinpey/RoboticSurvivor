#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "TitleScene.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("ファイル名");
	assert(hPict_ >= 0);
}

//更新
void TitleScene::Update()
{
}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TitleScene::Release()
{
}
