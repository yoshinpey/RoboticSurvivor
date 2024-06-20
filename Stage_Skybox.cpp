#include "Engine/Model.h"

#include "Stage_Skybox.h"
#include "Player.h"
#include "StageManager.h"

#include "PlayScene.h"
namespace 
{
	//Maxで950くらい
	XMFLOAT3 SphereScale = { 300,300,300 };
	std::string modelName = "Stage/skyBox.fbx";
}

Stage_Skybox::Stage_Skybox(GameObject* parent)
	:StageBase(parent, StageType::SKYBOX, "Stage_Skybox"), hModel_(-1)
{
}

Stage_Skybox::~Stage_Skybox()
{
	// ステージリストから削除する
	PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
	pPlayScene->GetStageManager()->RemoveCompletedStages(this);
}

void Stage_Skybox::Initialize()
{
	hModel_ = Model::Load(modelName);
	assert(hModel_ >= 0);

	transform_.scale_ = SphereScale;
}

void Stage_Skybox::Update()
{
	// スカイボックスはプレイヤーに付いて常に移動する
	Player* pPlayer = (Player*)FindObject("Player");
	if(pPlayer != nullptr)transform_.position_ = pPlayer->GetPosition();
	transform_.rotate_.y += 0.02f;
}

void Stage_Skybox::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, Direct3D::SHADER_TYPE::SHADER_SKYBOX);
}

void Stage_Skybox::Release()
{
}
