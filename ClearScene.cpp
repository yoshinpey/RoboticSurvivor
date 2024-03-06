#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "ClearScene.h"



ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hPict_(-1)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Pictures/Clear.jpg");
	assert(hPict_ >= 0);
}

void ClearScene::Update()
{
	// �f�o�b�O�p
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void ClearScene::Draw()
{
	// �摜�̃T�C�Y�擾
	XMFLOAT3 size = Image::GetTextureSize(hPict_);

	// �f�B�X�v���C�T�C�Y�ɍ��킹��
	transform_.scale_.x = (Direct3D::screenWidth_ / size.x);
	transform_.scale_.y = (Direct3D::screenHeight_ / size.y);

	// �`��ݒ�
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void ClearScene::Release()
{
}
