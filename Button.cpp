#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "TitleScene.h"
#include "Engine/Direct3D.h"
#include "AudioManager.h"

static XMFLOAT3 iSize = { 0.65f, 0.7f, 0 };
static XMFLOAT3 nSize = { 0.6f, 0.6f, 0 };

Button::Button(GameObject* parent) :
	GameObject(parent, "Button"), hPict_{ -1,-1 }, width_(0), height_(0), name_(""), widePos_{ 0,0,0 }, alpha_(255), frameAlpha_(255),
	isButtonInactive_(true), frameSize_{ 0, 0, 0 }, mode_(Direct3D::BLEND_ADD), isFirstPoint(true)
{
}

Button::~Button()
{
}

void Button::Initialize()
{
	alpha_ = 255;
	frameAlpha_ = 255;
}

void Button::Update()
{
	if (!isButtonInactive_)
		return;
	XMFLOAT3 mouse = Input::GetMousePositionSub();
	if (IsWithinBound()) {
		//�J�[�\�����d�Ȃ��Ă�Ƃ����Đ�
		if (isFirstPoint)
		{
			AudioManager::PlaySoundMa(AUDIO_POINTCURSOR);
			isFirstPoint = false;
		}
		transform_.scale_.x = iSize.x * width_;
		transform_.scale_.y = iSize.y * height_;
	}
	else {
		isFirstPoint = true;
		transform_.scale_.x = nSize.x * width_;
		transform_.scale_.y = nSize.y * height_;
	}
}

void Button::Draw()
{
	Direct3D::SetBlendMode(mode_);

	Image::SetAlpha(hPict_[1], frameAlpha_);
	Image::SetTransform(hPict_[1], transform_);
	Image::Draw(hPict_[1]);

	Image::SetAlpha(hPict_[0], alpha_);
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);


}

void Button::Release()
{
}

void Button::SetValue(float x, float y, float w, float h, std::string n)
{
	static float screenWidth = (float)GetSystemMetrics(SM_CXSCREEN);		//�X�N���[���̕�
	static float screenHeight = (float)GetSystemMetrics(SM_CYSCREEN);	//�X�N���[���̍���

	transform_.position_.x = x / screenWidth;
	transform_.position_.y = y / screenHeight;

	transform_.scale_.x = 0.6f;
	transform_.scale_.y = 0.6f;

	width_ = w;
	height_ = h;
	name_ = n;
	widePos_ = { x, y, 0 };

	std::string str1 = "Png/" + name_;
	std::string str2 = ".png";
	std::string str = str1 + str2;

	hPict_[0] = Image::Load(str);
	assert(hPict_[0] >= 0);

	// 1100 * 120
	hPict_[1] = Image::Load("Png/Frame.png");
	assert(hPict_[1] >= 0);
	frameSize_ = Image::GetTextureSize(hPict_[1]);

}

void Button::SetValue(float x, float y, float w, float h, std::string n, std::string frame)
{
	static float screenWidth = (float)GetSystemMetrics(SM_CXSCREEN);		//�X�N���[���̕�
	static float screenHeight = (float)GetSystemMetrics(SM_CYSCREEN);	//�X�N���[���̍���

	transform_.position_.x = x / screenWidth;
	transform_.position_.y = y / screenHeight;

	transform_.scale_.x = 0.6f;
	transform_.scale_.y = 0.6f;

	width_ = w;
	height_ = h;
	name_ = n;
	widePos_ = { x, y, 0 };

	std::string str1 = "Png/" + name_;
	std::string str2 = ".png";
	std::string str = str1 + str2;

	hPict_[0] = Image::Load(str);
	assert(hPict_[0] >= 0);

	str1 = "Png/" + frame;
	str2 = ".png";
	str = str1 + str2;

	hPict_[1] = Image::Load(str);
	assert(hPict_[1] >= 0);
	frameSize_ = Image::GetTextureSize(hPict_[1]);
}

bool Button::IsWithinBound()
{
	if (!isButtonInactive_)
		return false;

	XMFLOAT3 mouse = Input::GetMousePositionSub();
	mouse.x = -mouse.x;

	if (-mouse.y < (widePos_.y + (frameSize_.y * iSize.y) * height_) && -mouse.y >(widePos_.y - (frameSize_.y * iSize.y) * height_) &&
		-mouse.x < (widePos_.x + (frameSize_.x * iSize.x) * width_) && -mouse.x >(widePos_.x - (frameSize_.x * iSize.x) * width_))
		return true;

	return false;
}

void Button::SetBlendMode(int mode)
{
	mode_ = (Direct3D::BLEND_MODE)mode;
}