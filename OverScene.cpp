#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "OverScene.h"


//コンストラクタ
OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene"), hPict_(-1)
{
}

OverScene::~OverScene()
{
}

//初期化
void OverScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Pictures/Over.jpg");
	assert(hPict_ >= 0);
}

//更新
void OverScene::Update()
{
}

//描画
void OverScene::Draw()
{
	// 画像のサイズ取得
	XMFLOAT3 size = Image::GetTextureSize(hPict_);

	// ディスプレイサイズに合わせる
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	// 描画設定
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void OverScene::Release()
{
}
