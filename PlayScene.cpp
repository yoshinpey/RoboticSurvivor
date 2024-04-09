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
	// modelLoad
	std::vector<std::string> modelName =
	{
		"DebugCollision / sphereCollider.fbx",
		"Entity/Bullet.fbx"
	};
	////////////WaveTest
	XMFLOAT3 spawnPosition; // �X�|�[������ʒu

	// �o���̋�؂莞��
	int waveTimer = 300;
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
	
	////����̓G���o��������e�X�g
	for (int i=1; i<=20; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 5, 15), EnemyType::FLY);
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
	////////////////////////�f�o�b�N�p
	// �^�C�����E�F�[�u�X�|�[���̃e�X�g�p
	Timer* pTimer = static_cast<Timer*>(FindObject("Timer"));
	int time = pTimer->GetFrame();
	// �v���C���[�̈ʒu���g���đ��΍��W�ŏo��������p�̕ϐ�
	XMFLOAT3 plaPos = pPlayer_->GetPosition();
	//XMFLOAT3 plaDir = pPlayer_->CalculateMoveInput();

	if (time % waveTimer == 0)
	{
		// �E�F�[�u�̊J�n���ԂɂȂ�����G���X�|�[��������
		// �w�肵�����W�Ɏw�肵���G�𕡐��̃X�|�[��
		pEnemyManager_->SpawnMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(-5, 3, 5)),
			CalculateFloat3Add(plaPos, XMFLOAT3(5, 6, 10)),
			3,
			EnemyType::FLY
		);
	}
	
	if (time % waveTimer * 2 == 0)
	{

		// �w�肵�����W�Ɏw�肵���G���X�|�[��
		pEnemyManager_->SpawnEnemy(XMFLOAT3(plaPos.x, plaPos.y+3, plaPos.z + 5), EnemyType::FLY);
	}

	if (time % waveTimer * 0.5 == 0)
	{
		// �w�肵�����W�Ƀ����_���ȓG���o��������B
		pEnemyManager_->SpawnRandomMultiEnemy(XMFLOAT3(-20, 3, 20), XMFLOAT3(-10, 5, 30), 2);
	}

	if (time % waveTimer * 3 == 0)
	{
		// �w�肵�����W�Ƀ����_���ȓG���o��������B����t���C�����O���Ă�
		pEnemyManager_->SpawnRandomMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(10, 2, 10)),
			CalculateFloat3Add(plaPos, XMFLOAT3(20, 5, 20)),
			3
		);
	}

	//�G�����ׂď�������Q�[���N���A
	if (FindObject("Enemy_Fly") == nullptr && FindObject("Enemy_Ground") == nullptr && FindObject("Enemy_Explosion") == nullptr)
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