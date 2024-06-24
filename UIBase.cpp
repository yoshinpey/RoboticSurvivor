//#include "UIBase.h"
//#include "Engine/Image.h"
//#include "Engine/Direct3D.h"
//#include "Engine/Input.h"
//#include "AudioManager.h"
//
//namespace {
//	XMFLOAT2 BUTTON_SIZE = { 0.5f, 0.5f };
//
//}
//
//UIBase::UIBase()
//	:hPict_{ -1, -1, -1 }, alpha_{ 255 }, isBound_(false), widePos_(0.0f, 0.0f), frameSize_(0.0f, 0.0f)
//{
//}
//
//UIBase::~UIBase()
//{
//}
//
//void UIBase::Initialize(std::string name, XMFLOAT2 pos, XMFLOAT2 size, std::function<void()> onClick)
//{
//	const std::string fileName[] = { "Image/ButtonFrame1.png", "Image/ButtonFrame2.png", "Image/" + name + ".png" };
//	for (int i = 0; i < 3; i++) {
//		hPict_[i] = Image::Load(fileName[i]);
//		assert(hPict_[i] >= 0);
//	}
//
//	transform_.scale_ = XMFLOAT3(BUTTON_SIZE.x * size.x, BUTTON_SIZE.y * size.y, 1.0f);
//	transform_.position_.x = pos.x;
//	transform_.position_.y = pos.y;
//
//	XMFLOAT3 txtSi = Image::GetTextureSize(hPict_[0]);
//	frameSize_ = XMFLOAT2(txtSi.x * transform_.scale_.x / 2.0f, txtSi.y * transform_.scale_.y / 2.0f);
//
//	float screenWidth = (float)Direct3D::screenWidth_;		//�X�N���[���̕�
//	float screenHeight = (float)Direct3D::screenHeight_;	//�X�N���[���̍���
//	widePos_.x = screenWidth / 2.0f + screenWidth / 2.0f * transform_.position_.x;
//	widePos_.y = screenHeight / 2.0f + screenHeight / 2.0f * -transform_.position_.y;
//
//	onClick_ = onClick;
//}
//
//void UIBase::Draw()
//{
//	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
//
//	//�����ĂȂ�����false(0)������P���\�������
//	Image::SetTransform(hPict_[isBound_], transform_);
//	Image::Draw(hPict_[isBound_]);
//
//	//�e�L�X�g�̑傫���͕ς����ɕ\��
//	Transform text = transform_;
//	text.scale_ = { BUTTON_SIZE.x, BUTTON_SIZE.y, 1.f };
//	Image::SetTransform(hPict_[2], text);
//	Image::Draw(hPict_[2]);
//
//}
//
//bool UIBase::IsWithinBound()
//{
//	XMFLOAT3 mouse = Input::GetMousePosition();
//
//	if (mouse.y < widePos_.y + frameSize_.y && mouse.y > widePos_.y - frameSize_.y &&
//		mouse.x < widePos_.x + frameSize_.x && mouse.x > widePos_.x - frameSize_.x)
//	{
//		//�͈͓��ɓ���n�߂��特�Đ�
//		if (!isBound_) AudioManager::Play(AUDIO_TYPE::BUTTON_WITHIN);
//
//		isBound_ = true;
//		return true;
//	}
//
//	isBound_ = false;
//	return false;
//}
//
//void UIBase::OnClick()
//{
//	if (onClick_) {
//		AudioManager::Play(AUDIO_TYPE::BUTTON_PUSH);
//		onClick_();
//	}
//}