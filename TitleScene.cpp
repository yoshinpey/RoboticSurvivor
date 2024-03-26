#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "TitleScene.h"
#include "Engine/Input.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_{ -1,-1 }, transFlag(false)
{
}

TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_[0] = Image::Load("Pictures/Title.png");
	assert(hPict_[0] >= 0);

	hPict_[1] = Image::Load("Pictures/Start.png");
	assert(hPict_[1] >= 0);
}

//更新
void TitleScene::Update()
{
	// デバック用
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TitleScene::Draw()
{
	// 画像のサイズ取得
	XMFLOAT3 size = Image::GetTextureSize(hPict_[0]);

	// ディスプレイサイズに合わせる
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	if (textTrans_.scale_.x <= 1.5 && !transFlag)
	{
		textTrans_.scale_.x *= 1.01f;
		textTrans_.scale_.y *= 1.01f;
		if (textTrans_.scale_.x > 1.20f)
		{
			transFlag = true;
		}
	}

	if (transFlag)
	{
		textTrans_.scale_.x *= 0.99f;
		textTrans_.scale_.y *= 0.99f;
		if (textTrans_.scale_.x <= 0.60f)
		{
			transFlag = false;
		}
	}

	// 描画設定
	//Image::SetAlpha(hPict_, 100);
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);

	Image::SetTransform(hPict_[1], textTrans_);
	Image::Draw(hPict_[1]);
}


void TitleScene::Release()
{
}