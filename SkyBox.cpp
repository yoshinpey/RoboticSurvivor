#include "Engine/Model.h"

#include "SkyBox.h"
#include "Player.h"

namespace 
{
	//Max��950���炢
	XMFLOAT3 SPHERE_SCALE = { 300,300,300 };
	std::string modelName = "Stage/skyBox.fbx";     // ���f����
}

SkyBox::SkyBox(GameObject* parent)
	:GameObject(parent, "SkyBox"), hModel_(-1), pPlayer_(nullptr)
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::Initialize()
{
	hModel_ = Model::Load(modelName);
	assert(hModel_ >= 0);

	transform_.scale_ = SPHERE_SCALE;
	pPlayer_ = (Player*)FindObject("Player");
}

void SkyBox::Update()
{
	// �X�J�C�{�b�N�X�̓v���C���[�ɕt���ď�Ɉړ�����
	if (pPlayer_ != nullptr) transform_.position_ = pPlayer_->GetPosition();	
}

void SkyBox::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, Direct3D::SHADER_TYPE::SHADER_SKYBOX);
}

void SkyBox::Release()
{
}
