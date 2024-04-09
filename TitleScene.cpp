#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "TitleScene.h"
#include "Engine/Input.h"


//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_{ -1,-1 }, transFlag(false)
{
}

TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_[0] = Image::Load("Pictures/Title.png");
	assert(hPict_[0] >= 0);

	hPict_[1] = Image::Load("Pictures/Start.png");
	assert(hPict_[1] >= 0);
}

//�X�V
void TitleScene::Update()
{
	// �f�o�b�N�p
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//�`��
void TitleScene::Draw()
{
	// �摜�̃T�C�Y�擾
	XMFLOAT3 size = Image::GetTextureSize(hPict_[0]);

	// �f�B�X�v���C�T�C�Y�ɍ��킹��
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	if (textTrans_.scale_.x <= 1.5 && !transFlag)
	{
		textTrans_.scale_.x *= 1.01f;
		textTrans_.scale_.y *= 1.01f;
		if (textTrans_.scale_.x > 1.20f)
		{
			transFlag = true;
		}
	}

	if (transFlag)
	{
		textTrans_.scale_.x *= 0.99f;
		textTrans_.scale_.y *= 0.99f;
		if (textTrans_.scale_.x <= 0.60f)
		{
			transFlag = false;
		}
	}

	// �`��ݒ�
	//Image::SetAlpha(hPict_, 100);
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);

	Image::SetTransform(hPict_[1], textTrans_);
	Image::Draw(hPict_[1]);
}


void TitleScene::Release()
{
}