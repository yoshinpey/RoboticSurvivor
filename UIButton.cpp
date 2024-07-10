#include "UIButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "AudioManager.h"


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

}

bool UIButton::checkHover()
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