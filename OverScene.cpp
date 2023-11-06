#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "OverScene.h"


//�R���X�g���N�^
OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene"), hPict_(-1)
{
}

//������
void OverScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("�t�@�C����");
	assert(hPict_ >= 0);
}

//�X�V
void OverScene::Update()
{
}

//�`��
void OverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void OverScene::Release()
{
}
