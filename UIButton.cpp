#include "UIButton.h"
#include "Engine/Image.h"

UIButton::UIButton(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick)
    : UIBase(name, pos, size), onClick_(onClick),
	hButtonPict_{ -1, -1 }, alpha_{ 255 }, isHovered_(false), widePos_(0.0f, 0.0f), frameSize_(0.0f, 0.0f)
{
	// フレームと使いたい文字画像をロードする
	const std::string fileName[] =
	{
		"Pictures/ButtonFrame1.png",
		"Pictures/ButtonFrame2.png"
	};

	for (int i = 0; i < 2; ++i)
	{
		hButtonPict_[i] = Image::Load(fileName[i]);
		assert(hButtonPict_[i] >= 0);
	}

	hTextPict_ = Image::Load("Pictures/" + name + ".png");
	assert(hTextPict_ >= 0);

}