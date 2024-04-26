#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

#include "PlayScene.h"
#include "GameManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Ground.h"
#include "Timer.h"
#include "Score.h"
#include "SkyBox.h"
#include "Engine/Model.h"

namespace
{
	// LoadModels
	std::vector<std::string> modelName =
	{
		"DebugCollision / sphereCollider.fbx",
		"Entity/Bullet.fbx",
		"Enemy/Enemy_Ground.fbx",
		"Enemy/Enemy_Fly.fbx",
		"Enemy/Enemy_Explosion.fbx"
	};
	////////////WaveTest
	XMFLOAT3 spawnPosition;		// �X�|�[������ʒu
	int waveTimer = 300;		// �o���̋�؂莞��
}

PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), pEnemyManager_(nullptr), pSceneManager_(nullptr), pPlayer_(nullptr)
{
	pEnemyManager_ = new EnemyManager(this);
	pSceneManager_ = (SceneManager*)FindObject("SceneManager");
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	// �V�[���̓r���œo�ꂷ�郂�f���͐�ɓǂ�ł���
	for (int i = 0; i < modelName.size(); ++i)
	{
		Model::Load(modelName[i]);
	}

	Instantiate<Ground>(this);			// �n�ʓo��
	Instantiate<SkyBox>(this);			// ��o��
	pPlayer_=Instantiate<Player>(this);			//�v���C���[�o��
	
	///////////////////����̓G���o��������e�X�g
	for (int i = 0; i < 30; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 0, 5), EnemyType::EXPLOSION);
	}
	for (int i = 0; i < 15; i += 5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 5, 20), EnemyType::GROUND);
	}
	for (int i = 0; i < 15; i += 5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 10, 20), EnemyType::FLY);
	}
	//��UI�n���͑O�ʂɂȂ�悤�ɕ`��
	Instantiate<Timer>(this);			//�^�C�}�[�o��
	Instantiate<Score>(this);			//�X�R�A�\��

	//�^�C�}�[�ݒ�
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(30);
	t->Start();
}

void PlayScene::Update()
{
	////////////////////////�G�̌̐��f�o�b�O���O
	static float count[4] = {0,0,0,0};
	count[0] = pEnemyManager_->GetEnemyCount(EnemyType::GROUND);
	count[1] = pEnemyManager_->GetEnemyCount(EnemyType::EXPLOSION);
	count[2] = pEnemyManager_->GetEnemyCount(EnemyType::FLY); 
	count[3] = pEnemyManager_->GetEnemyCount(); 
	std::string output = 
		"Ground		: " + std::to_string(count[0]) + "\n"
		"Explosion	: " + std::to_string(count[1]) + "\n"
		"Fly			: " + std::to_string(count[2]) + "\n"
		"All			: " + std::to_string(count[3]) + "\n";
	if(Input::IsKeyDown(DIK_TAB))
		OutputDebugStringA(output.c_str());

	//////////////////////////�f�o�b�N�p
	//// �^�C�����E�F�[�u�X�|�[���̃e�X�g�p
	//Timer* pTimer = static_cast<Timer*>(FindObject("Timer"));
	//int time = pTimer->GetFrame();
	//// �v���C���[�̈ʒu���g���đ��΍��W�ŏo��������p�̕ϐ�
	//XMFLOAT3 plaPos = pPlayer_->GetPosition();
	////XMFLOAT3 plaDir = pPlayer_->CalculateMoveInput();

	//if (time % waveTimer == 0)
	//{
	//	// �E�F�[�u�̊J�n���ԂɂȂ�����G���X�|�[��������
	//	// �w�肵�����W�Ɏw�肵���G�𕡐��̃X�|�[��
	//	pEnemyManager_->SpawnMultiEnemy
	//	(
	//		CalculateFloat3Add(plaPos, XMFLOAT3(-5, 3, 5)),
	//		CalculateFloat3Add(plaPos, XMFLOAT3(5, 6, 10)),
	//		3,
	//		EnemyType::FLY
	//	);
	//}
	//
	//if (time % waveTimer * 2 == 0)
	//{

	//	// �w�肵�����W�Ɏw�肵���G���X�|�[��
	//	pEnemyManager_->SpawnEnemy(XMFLOAT3(plaPos.x, plaPos.y+3, plaPos.z + 5), EnemyType::FLY);
	//}

	//if (time % waveTimer * 0.5 == 0)
	//{
	//	// �w�肵�����W�Ƀ����_���ȓG���o��������B
	//	pEnemyManager_->SpawnRandomMultiEnemy(XMFLOAT3(-20, 3, 20), XMFLOAT3(-10, 5, 30), 2);
	//}

	//if (time % waveTimer * 3 == 0)
	//{
	//	// �w�肵�����W�Ƀ����_���ȓG���o��������B����t���C�����O���Ă�
	//	pEnemyManager_->SpawnRandomMultiEnemy
	//	(
	//		CalculateFloat3Add(plaPos, XMFLOAT3(10, 2, 10)),
	//		CalculateFloat3Add(plaPos, XMFLOAT3(20, 5, 20)),
	//		3
	//	);
	//}

	//�G�����ׂď�������Q�[���N���A
	if (pEnemyManager_->GetEnemyCount() == 0)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}
	// ���Ԑ؂�
	if (time == 0)
	{
		pEnemyManager_->RemoveAllEnemies();
		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}
	//////////////////////////////////////

	// ����̃G�l�~�[����
	if (Input::IsKeyDown(DIK_4))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::GROUND);
	}

	// �S���̃G�l�~�[�����Y
	if (Input::IsKeyDown(DIK_5))
	{
		pEnemyManager_->RemoveAllEnemies();
	}


	//////�X�R�A�e�X�g�p
	//Score* s = (Score*)FindObject("Score");
	//static float score = 0;	
	//static int num = 0;
	//num++;
	//score = (num % 60) * 0.1f;

	//s->ScoreAdd((int)score);
	////////////////////////
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
	SAFE_DELETE(pEnemyManager_);
}