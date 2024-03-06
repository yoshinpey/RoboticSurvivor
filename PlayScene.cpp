#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "GameManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "PlayScene.h"
#include "Ground.h"
#include "Timer.h"
#include "Gauge.h"
#include "Score.h"
#include "SkyBox.h"

PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), pEnemyManager_(nullptr), pSceneManager_(nullptr)
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
	Model::Load("DebugCollision/sphereCollider.fbx");
	Model::Load("Entity/Bullet.fbx");

	Instantiate<Ground>(this);			//�n�ʓo��

	pPlayer_=Instantiate<Player>(this);			//�v���C���[�o��
	Instantiate<SkyBox>(this);			//�v���C���[�o��

	////����̓G���o��������e�X�g
	for (int i=1; i<=20; i+=5)
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(0, 0, 15), EnemyType::FLY);
	}
	

	//��UI�n���͑O�ʂɂȂ�悤�ɕ`��
	Instantiate<Timer>(this);			//�^�C�}�[�o��
	Instantiate<Gauge>(this);			//HP�Q�[�W	
	Instantiate<Score>(this);			//�X�R�A�\��

	//�^�C�}�[�ݒ�
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(5);
	t->Start();
}

void PlayScene::Update()
{

	////////////////////////�f�o�b�N�p
	// �G�̏o���e�X�g 
	// �v���C���[�̈ʒu���g���đ��΍��W�ŏo��������p�̕ϐ�
	XMFLOAT3 plaPos = pPlayer_->GetPosition();

	// �w�肵�����W�Ɏw�肵���G���X�|�[��
	if (Input::IsKeyDown(DIK_1))
	{
		pEnemyManager_->SpawnEnemy(XMFLOAT3(plaPos.x, plaPos.y, plaPos.z + 5), EnemyType::FLY);
	}
	
	// �w�肵�����W�Ɏw�肵���G�𕡐��̃X�|�[��
	if (Input::IsKeyDown(DIK_2))
	{
		pEnemyManager_->SpawnMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(0, 0, 5)),
			CalculateFloat3Add(plaPos, XMFLOAT3(0, 0, 10)),
			3, 
			EnemyType::FLY);
	}

	// �w�肵�����W�Ƀ����_���ȓG���o��������B
	if (Input::IsKeyDown(DIK_3))
	{
		pEnemyManager_->SpawnRandomMultiEnemy(XMFLOAT3(-20, 0, 20), XMFLOAT3(-10, 0, 30), 2);
	}

	// �w�肵�����W�Ƀ����_���ȓG���o��������B����O���E���h�����O���Ă�
	if (Input::IsKeyDown(DIK_4))
	{
		pEnemyManager_->SpawnRandomMultiEnemy
		(
			CalculateFloat3Add(plaPos, XMFLOAT3(10, 2, 10)),
			CalculateFloat3Add(plaPos, XMFLOAT3(20, 5, 20)),
			3,
			EnemyType::GROUND);
	}



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





	TimeProcess();	

	// �^�C�����E�F�[�u�X�|�[���̃e�X�g�p
	Timer* t = (Timer*)FindObject("Timer");
	int time = t->GetFlame();
	if (time % 300 == 0)
	{
		for (int i = 1; i < 20; i+=4)
		{
			pEnemyManager_->SpawnEnemy(XMFLOAT3(i, 0, 30), EnemyType::GROUND);
		}
	}

	// ���Ԑ؂�
	if (time == 0)
	{
		pEnemyManager_->RemoveAllEnemies();
		
		pSceneManager_->ChangeScene(SCENE_ID_OVER);
	}


	//////�X�R�A�e�X�g�p
	Score* s = (Score*)FindObject("Score");
	static float score = 0;	
	static int num = 0;
	num++;
	score = (num % 60) * 0.1f;

	s->ScoreAdd((int)score);

	// �f�o�b�O
	//�G�����ׂď�������Q�[���N���A
	if (FindObject("Enemy_Fly") == nullptr&& FindObject("Enemy_Ground") == nullptr && FindObject("Enemy_Explosion") == nullptr)
	{
		pSceneManager_->ChangeScene(SCENE_ID_CLEAR);
	}
	////////////////////////
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
	SAFE_DELETE(pEnemyManager_);
}

//�^�C�}�[
void PlayScene::TimeProcess()
{
#ifdef _DEBUG

	//�^�C�}�[�N��
	if (Input::IsKeyDown(DIK_T))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->Start();
	}
	//�^�C�}�[�ꎞ��~
	if (Input::IsKeyDown(DIK_Y))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->Stop();
	}
#endif
}
