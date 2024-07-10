#include "UIButton .h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"

#include "AudioManager.h"
#include "UIButton.h"

namespace
{
}

UIButton ::UIButton (std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick)
	: hPict_{ -1, -1, -1 }, alpha_{ 255 }, isHovered_(false), widePos_(0.0f, 0.0f), frameSize_(0.0f, 0.0f)
{
}

UIButton ::~UIButton ()
{
}



void UIButton ::Initialize()
{


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

void UIButton ::Draw()
{
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

	//押してない時はfalse(0)だから１が表示される
	Image::SetTransform(hPict_[isBound_], transform_);
	Image::Draw(hPict_[isBound_]);

	//テキストの大きさは変えずに表示
	Transform text = transform_;
	text.scale_ = { BUTTON_SIZE.x, BUTTON_SIZE.y, 1.0f };
	Image::SetTransform(hPict_[2], text);
	Image::Draw(hPict_[2]);

}

bool UIButton ::IsWithinBound()
{

}

void UIButton ::OnClick()
{
	if (onClick_)
	{
		AudioManager::Play(AUDIO_ID::CURSOR_ENTER);
		onClick_();
	}
}