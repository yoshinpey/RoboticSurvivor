#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "OverScene.h"


//コンストラクタ
OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene"), hPict_(-1)
{
}

//初期化
void OverScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("ファイル名");
	assert(hPict_ >= 0);
}

//更新
void OverScene::Update()
{
}

//描画
void OverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void OverScene::Release()
{
}
