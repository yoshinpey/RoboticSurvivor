#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "TitleScene.h"
#include "Engine/Input.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Pictures/Title.jpg");
	assert(hPict_ >= 0);
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
	XMFLOAT3 size = Image::GetTextureSize(hPict_);

	// ディスプレイサイズに合わせる
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	// 描画設定
	//Image::SetAlpha(hPict_, 100);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TitleScene::Release()
{
}
