#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "TitleScene.h"
#include <cmath>

namespace 
{
	const float defaultScale = 1.00f;	// 標準の大きさ
	const float minScale = 0.80f;		// 最大画像サイズ
	const float maxScale = 1.20f;		// 最小画像サイズ
	const float stepScale = 0.02f;		// 時間経過による変化量
	const float frequency = 4.0f;		// 頻度
}

// コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), time_(0.0f)
{
}

TitleScene::~TitleScene()
{
}

// 初期化
void TitleScene::Initialize()
{
	// 画像のパス
	std::vector<std::string> picturePaths =
	{
		"Pictures/Title.png",
		"Pictures/Start.png"
	};

	// 画像データのロード
	for (int i = 0; i < picturePaths.size(); ++i)
	{
		int handle = Image::Load(picturePaths[i]);
		assert(handle >= 0);
		hPict_.push_back(handle);
	}

	// 背景画像のサイズ取得
	XMFLOAT3 size = Image::GetTextureSize(hPict_[TITLE]);

	// ウィンドウに合わせる
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	// スタートテキスト画像の位置をウィンドウの中央に設定する
	// 画像の配置：-1＝左端、0＝中央、1＝右端
	XMFLOAT2 textPosition = {0,0};
	textTrans_.position_.x = textPosition.x;
	textTrans_.position_.y = textPosition.y;
}

// 更新
void TitleScene::Update()
{
	// キー入力があったらゲームを開始する
	if (Input::GetKeyCode() != 0)
	{
		SceneManager* pSceneManager = static_cast<SceneManager*>(FindObject("SceneManager"));
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
	
	// サインカーブを使ったスタートテキストの拡大縮小
	time_ += stepScale;
	float scale = minScale + (maxScale - minScale) * (0.5f * (1.0f + sinf(frequency * time_)));
	textTrans_.scale_.x = scale;
	textTrans_.scale_.y = scale;
}

// 描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_[TITLE], transform_);
	Image::Draw(hPict_[TITLE]);

	Image::SetTransform(hPict_[START], textTrans_);
	Image::Draw(hPict_[START]);
}

void TitleScene::Release()
{
}