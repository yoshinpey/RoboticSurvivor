#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "TitleScene.h"
#include "Engine/Input.h"


//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Pictures/Title.jpg");
	assert(hPict_ >= 0);
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
	XMFLOAT3 size = Image::GetTextureSize(hPict_);

	// �f�B�X�v���C�T�C�Y�ɍ��킹��
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	// �`��ݒ�
	//Image::SetAlpha(hPict_, 100);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleScene::Release()
{
}
