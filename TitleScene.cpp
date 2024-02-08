#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "TitleScene.h"
#include "Engine/Input.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Title.jpg");
	assert(hPict_ >= 0);
}

//更新
void TitleScene::Update()
{
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
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
