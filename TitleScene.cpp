#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "TitleScene.h"
#include <cmath>

namespace 
{
	const float defaultScale = 1.00f;	// �W���̑傫��
	const float minScale = 0.80f;		// �ő�摜�T�C�Y
	const float maxScale = 1.20f;		// �ŏ��摜�T�C�Y
	const float stepScale = 0.02f;		// ���Ԍo�߂ɂ��ω���
	const float frequency = 4.0f;		// �p�x
}

// �R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), time_(0.0f)
{
}

TitleScene::~TitleScene()
{
}

// ������
void TitleScene::Initialize()
{
	// �摜�̃p�X
	std::vector<std::string> picturePaths =
	{
		"Pictures/Title.png",
		"Pictures/Start.png"
	};

	// �摜�f�[�^�̃��[�h
	for (int i = 0; i < picturePaths.size(); ++i)
	{
		int handle = Image::Load(picturePaths[i]);
		assert(handle >= 0);
		hPict_.push_back(handle);
	}

	// �w�i�摜�̃T�C�Y�擾
	XMFLOAT3 size = Image::GetTextureSize(hPict_[TITLE]);

	// �E�B���h�E�ɍ��킹��
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	// �X�^�[�g�e�L�X�g�摜�̈ʒu���E�B���h�E�̒����ɐݒ肷��
	// �摜�̔z�u�F-1�����[�A0�������A1���E�[
	XMFLOAT2 textPosition = {0,0};
	textTrans_.position_.x = textPosition.x;
	textTrans_.position_.y = textPosition.y;
}

// �X�V
void TitleScene::Update()
{
	// �L�[���͂���������Q�[�����J�n����
	if (Input::GetKeyCode() != 0)
	{
		SceneManager* pSceneManager = static_cast<SceneManager*>(FindObject("SceneManager"));
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
	
	// �T�C���J�[�u���g�����X�^�[�g�e�L�X�g�̊g��k��
	time_ += stepScale;
	float scale = minScale + (maxScale - minScale) * (0.5f * (1.0f + sinf(frequency * time_)));
	textTrans_.scale_.x = scale;
	textTrans_.scale_.y = scale;
}

// �`��
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