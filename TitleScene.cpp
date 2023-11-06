#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "TitleScene.h"


//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("�t�@�C����");
	assert(hPict_ >= 0);
}

//�X�V
void TitleScene::Update()
{
}

//�`��
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleScene::Release()
{
}
