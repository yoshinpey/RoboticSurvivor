#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "OverScene.h"


//�R���X�g���N�^
OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene"), hPict_(-1)
{
}

OverScene::~OverScene()
{
}

//������
void OverScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Pictures/Over.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void OverScene::Update()
{
}

//�`��
void OverScene::Draw()
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

//�J��
void OverScene::Release()
{
}
