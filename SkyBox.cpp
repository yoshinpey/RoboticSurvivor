#include "Engine/Model.h"

#include "SkyBox.h"
#include "Player.h"

namespace {
	//Maxで950くらい
	XMFLOAT3 SPHERE_SCALE = { 300,300,300 };
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
	hModel_ = Model::Load("Stage/skyBox.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = SPHERE_SCALE;
	pPlayer_ = (Player*)FindObject("Player");
}

void SkyBox::Update()
{
	// スカイボックスはプレイヤーにつける
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
