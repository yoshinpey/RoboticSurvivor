#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "ClearScene.h"



ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hPict_(-1)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Pictures/Clear.jpg");
	assert(hPict_ >= 0);
}

void ClearScene::Update()
{
	// デバッグ用
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void ClearScene::Draw()
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

void ClearScene::Release()
{
}
