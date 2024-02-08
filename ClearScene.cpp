#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "ClearScene.h"


//コンストラクタ
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hPict_(-1)
{
}

//初期化
void ClearScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Clear.jpg");
	assert(hPict_ >= 0);
}

//更新
void ClearScene::Update()
{
}

//描画
void ClearScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void ClearScene::Release()
{
}
