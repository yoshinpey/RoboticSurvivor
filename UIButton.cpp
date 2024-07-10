#include "UIButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "AudioManager.h"
#include "Engine/Direct3D.h"


UIButton::UIButton(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick)
    : UIBase(name, pos, size), onClick_(onClick), alpha_{ 255 }, isHovered_(false), widePos_(0.0f, 0.0f), frameSize_(0.0f, 0.0f)
{
	// フレームと使いたい文字画像をロードする
	std::array<std::string, ButtonPictures::MAX> pictNames =
	{
		"Pictures/ButtonFrame1.png",
		"Pictures/ButtonFrame2.png",
		"Pictures/" + name + ".png"
	};

	for (int i = 0; i < pictNames.size(); ++i)
	{
		hPict_[i] = Image::Load(pictNames[i]);
		assert(hPict_[i] >= 0);
	}

	transform_.scale_ = XMFLOAT3(size.x, size.y, 1.0f);
	transform_.position_.x = pos.x;
	transform_.position_.y = pos.y;

	XMFLOAT3 txtSi = Image::GetTextureSize(hPict_[0]);
	frameSize_ = XMFLOAT2(txtSi.x * transform_.scale_.x / 2.0f, txtSi.y * transform_.scale_.y / 2.0f);

	float screenWidth = (float)Direct3D::screenWidth_;		//スクリーンの幅
	float screenHeight = (float)Direct3D::screenHeight_;	//スクリーンの高さ
	widePos_.x = screenWidth / 2.0f + screenWidth / 2.0f * transform_.position_.x;
	widePos_.y = screenHeight / 2.0f + screenHeight / 2.0f * -transform_.position_.y;

	onClick_ = onClick;
}

UIButton::~UIButton()
{
}

bool UIButton::CheckingHover()
{
	XMFLOAT3 cursorPosition = Input::GetMousePosition();

	if (cursorPosition.y < widePos_.y + frameSize_.y && cursorPosition.y > widePos_.y - frameSize_.y &&
		cursorPosition.x < widePos_.x + frameSize_.x && cursorPosition.x > widePos_.x - frameSize_.x)
	{
		//範囲内に入った時に音を再生
		if (!isHovered_) AudioManager::Play(AUDIO_ID::CURSOR_POINT);

		isHovered_ = true;
		return true;
	}

	isHovered_ = false;
	return false;
}

void UIButton::OnClick()
{
	if (onClick_)
	{
		AudioManager::Play(AUDIO_ID::CURSOR_ENTER);
		onClick_();
	}
}


void UIButton::Draw()
{
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

	// 重なってないときはfalse(0)だからButtonFrame1が表示される
	// 重なっているときはtrue(1)だからButtonFrame2が表示される
	Image::SetTransform(hPict_[isHovered_], transform_);
	Image::Draw(hPict_[isHovered_]);

	//テキストの表示
	Image::SetTransform(hPict_[TEXT], transform_);
	Image::Draw(hPict_[TEXT]);

}