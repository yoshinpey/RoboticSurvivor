#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "Timer.h"
#include "Score.h"
#include "SkyBox.h"

#include "AudioManager.h"
#include "EffectManager.h"
#include "EnemyManager.h"

#include <array>

namespace
{
	// ���̃V�[���Ŏg�p���郂�f���Q
	std::array<std::string, 6> modelName = 
	{
		"DebugCollision/sphereCollider.fbx",
		"Entity/Bullet.fbx",
		"Entity/Missile.fbx",
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
	/////////////////////////////////////////
	AudioManager::Initialize();
	EffectManager::Initialize();
	/////////////////////////////////////////
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	// �V�[���̓r���œo�ꂷ�郂�f���͐�Ƀ��[�h�������Ă���(���O�΍�)
	for (int i = 0; i < modelName.size(); ++i)
	{
		Model::Load(modelName[i]);
	}

	Instantiate<Stage>(this);			// �n�ʓo��
	Instantiate<SkyBox>(this);			// ��o��
	pPlayer_=Instantiate<Player>(this);			//�v���C���[�o��
	
	///////////////////����̓G���o��������e�X�g
	for (int i = -10; i < 10; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 0, 5), EnemyType::GROUND);
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
	//�G�����ׂď�������Q�[���N���A
	if (pEnemyManager_->GetEnemyCount() == 0)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}

	Timer* pTimer = static_cast<Timer*>(FindObject("Timer"));

	// ���Ԑ؂�
	if (pTimer->IsFinished() || pPlayer_ == nullptr)
	{
		pEnemyManager_->RemoveAllEnemies();
		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}

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

	////////////////////////�f�o�b�N�p

	// �v���C���[����Ƃ�������������
	if (!pPlayer_)return;

	// �v���C���[�̈ʒu���g���đ��΍��W�ŏo��������p�̕ϐ�
	XMFLOAT3 plaPos = pPlayer_->GetPosition();
	XMFLOAT3 plaDir = pPlayer_->CalculateMoveInput();
	//plaPos = CalculateFloat3Add(plaPos, plaDir);

	if (pTimer->GetFrame() % waveTimer * 3 == 0)
	{
		XMFLOAT3 minPos = XMFLOAT3(-5, 3, 5);
		XMFLOAT3 maxPos = XMFLOAT3(5, 6, 10);
		int count = 3;
		std::vector<EnemyType> enemyID = { EnemyType::EXPLOSION, EnemyType::FLY };

		// �w�肵�����W�Ƀ����_���ȓG���o��������B���񔚔��ƃt���C����I��
		pEnemyManager_->SpawnRandomMultiEnemy
		(
			CalculateFloat3Add(plaPos, minPos),
			CalculateFloat3Add(plaPos, maxPos),
			count,
			enemyID
		);
	}
	//////////////////////////////////////

	// ����̃G�l�~�[����
	if (Input::IsKeyDown(DIK_1))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::FLY);
	}
	if (Input::IsKeyDown(DIK_2))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::GROUND);
	}
	if (Input::IsKeyDown(DIK_3))
	{
		pEnemyManager_->RemoveEnemy(EnemyType::EXPLOSION);
	}

	// �S���̃G�l�~�[�����Y
	if (Input::IsKeyDown(DIK_4))
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
}

void PlayScene::CheckAndChangeScene()
{
	// �G�����ׂď�������Q�[���N���A
	if (pEnemyManager_->GetEnemyCount() == 0)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}

	Timer* pTimer = static_cast<Timer*>(FindObject("Timer"));

	// ���Ԑ؂�A���邢�̓v���C���[�̎��S
	if (pTimer->IsFinished() || pPlayer_ == nullptr)
	{
		pEnemyManager_->RemoveAllEnemies();
		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}
}